/* COP 3502C PA5
    This program is written by: Jeronimo Leon */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 30

typedef struct Monster
{
    char *name;                
    char element[MAXSIZE + 1]; 
    int power; 
} Monster;

typedef struct BST_Node
{
    Monster *monster;
    struct BST_Node *left;
    struct BST_Node *right;
} BST_Node;

// numeric protocol opcodes read from stdin
typedef enum OpCode
{
    OP_REGISTER = 1, // Insert a new monster if absent
    OP_REMOVE   = 2, // Delete an existing monster by name
    OP_FIND     = 3, // Look up a monster by name
    OP_NEXT     = 4, // Find smallest name strictly > query
    OP_RANGE    = 5, // Count names in low - high
    OP_DISPLAY  = 6  // Print monsters in alphabetical order via in-order traversal, or aas EMPTY
} OpCode;

// compares a search key against a node's name
static int compareKey(const char *key, const BST_Node *node)
{
    // Returns <0 if key belongs left, >0 if key belongs right
    // 0 if exact match
    return strcmp(key, node->monster->name);
}

// Allocate and initialize 3 heap blocks for one newly registered monster
static BST_Node *createNode(const char *name, const char *element, int power)
{
    // Block 1: allocate the tree nodes shell to 24 bytes 
    BST_Node *node = (BST_Node *)malloc(sizeof(BST_Node));
    // Block 2: allocate the Monster record to hold 48 bytes 
    Monster *monster = (Monster *)malloc(sizeof(Monster));

    // Block 3: allocate bytes for name + 1 byte for the '\0' null terminator
    monster->name = (char *)malloc(strlen(name) + 1);
    // copy name out of main's stack buffer so it survives future input lines
    strcpy(monster->name, name);
    // Copy element directly into the fixed 31-byte array inside Monster
    strcpy(monster->element, element);
    // Store the integer power score by value
    monster->power = power;

    // Attach the Monster data to the BST_Node
    node->monster = monster;
    // Initialize child pointers to NULL
    node->left = NULL;
    node->right = NULL;
    // Return the new leaf node to caller for tree attachment
    return node;
}

// releases a node's 3 heap blocks in strict reverse creation order
static void destroyNode(BST_Node *node)
{
    // 1st free: release the innermost name buffer
    free(node->monster->name);
    // 2nd free: release the Monster struct 
    free(node->monster);
    // 3rd free: release the outermost BST_Node shell last
    free(node);
}

// Search for exact name, return matching node pointer or NULL
static BST_Node *search(BST_Node *root, const char *name)
{
    // Holds the strcmp result to compare strings per level
    int cmp;

    // Base case
    if (root == NULL)
    {
        return NULL;
    }

    // Compare target name against the current nodes name
    cmp = compareKey(name, root);
    // Exact match found, stop descending and return this node
    if (cmp == 0)
    {
        return root;
    }
    // Target is alphabetically smaller, discard root and right subtree, search left
    if (cmp < 0)
    {
        return search(root->left, name);
    }
    // Target is alphabetically larger, discard root and left subtree, search right
    return search(root->right, name);
}

// Attaches a leaf node at its sorted NULL gap
static BST_Node *insert(BST_Node *root, BST_Node *newNode)
{
    // Base case, NULL gap where newNode belongs, return to parent
    if (root == NULL)
    {
        return newNode;
    }

    // Decide branch by comparing newNode's name against current nodes name
    if (compareKey(newNode->monster->name, root) < 0)
    {
        // Recursively insert into left subtree
        root->left = insert(root->left, newNode);
    }
    else
    {
        // Precondition guarantees no duplicates, so non-negative means strictly greater
        root->right = insert(root->right, newNode);
    }
    // Hand subtrees unchanged root pointer back up to its parent
    return root;
}

// Walking or walks left to the alphabetically smallest node in a non-empty subtree
static BST_Node *minNode(BST_Node *root)
{
    // Keeps stepping left until no smaller child exists
    while (root->left != NULL)
    {
        root = root->left;
    }
    // Left node is the minimum, has root->left == NULL
    return root;
}

// Removes the names in O(h) time across the 3 BST cases, returns updated subtree root
static BST_Node *deleteNode(BST_Node *root, const char *name)
{
    // Stores strcmp result at the current node
    int cmp;

    // base case: nothing to delete in an empty subtree
    if (root == NULL)
    {
        return NULL;
    }

    // Navigate towards the node to remove
    cmp = compareKey(name, root);
    if (cmp < 0)
    {
        // Target is in the left subtree, reconnect the parents left link to subtree
        root->left = deleteNode(root->left, name);
    }
    else if (cmp > 0)
    {
        // Target is in the right subtree, reconnect parents right link to subtrees
        root->right = deleteNode(root->right, name);
    }
    else
    {
        // Found the node to delete, check and confirm which of the 3 structural cases applies
        // Case 1: leaf is NULL on both 
        if (root->left == NULL)
        {
            // Save replacement subtree before freeing root
            BST_Node *rightChild = root->right;
            // Free all 3 heap blocks of the deleted monster
            destroyNode(root);
            // Return rightChild, so parent bypasses the deleted node
            return rightChild;
        }
        // Case 2, only left child exists
        if (root->right == NULL)
        {
            // Save the left subtree before freeing root
            BST_Node *leftChild = root->left;
            // Free all heap blocks of the deleted monster
            destroyNode(root);
            // Return leftChild, so parent bypasses the deleted node
            return leftChild;
        }

        // Case 3: two children, replacing with the in-order successor
        {
            // In-order successor is the minimum, the left-most node of the right subtree
            BST_Node *succ = minNode(root->right);
            // Swap Monster * pointers, so each node still owns 1 unique Monster
            Monster *tmp = root->monster;
            root->monster = succ->monster;
            succ->monster = tmp;
            
            // Delete original name from right subtree
            root->right = deleteNode(root->right, name);
        }
    }
    // Return subtrees root pointer back to its parent
    return root;
}

// Find smallest stored name
static BST_Node *successor(BST_Node *root, const char *query)
{
    // Base case
    if (root == NULL)
    {
        return NULL;
    }

    if (compareKey(query, root) < 0)
    {
        // root is a valid candidate, search left subtree for an even smaller valid name
        BST_Node *better = successor(root->left, query);
        // If left subtree found a tighter candidate, propagate it up, else root wins
        return (better != NULL) ? better : root;
    }

    // root->name <= query, neither root or left subtree can be strictly greater
    return successor(root->right, query);
}

// Counts names with low <= name <= high recursively, pruning impossible subtrees
static int countRange(BST_Node *root, const char *low, const char *high)
{
    // Base case: empty subtree has 0 qualifying monsters
    if (root == NULL)
    {
        return 0;
    }

    // means root->name < low, prune entire left subtree
    if (compareKey(low, root) > 0)
    {
        return countRange(root->right, low, high);
    }
    // root->name > high, prune entire right subtree
    if (compareKey(high, root) < 0)
    {
        return countRange(root->left, low, high);
    }

    // Node lies inside low - high, counts it plus qualifying counts from both sides
    return 1 + countRange(root->left, low, high) + countRange(root->right, low, high);
}

// Print every monster in ascending alphabetical order using recursive in-order traversal
static void inorderDisplay(const BST_Node *root)
{
    // Base case: reached empty branch, return without printing
    if (root == NULL)
    {
        return;
    }
    // Visit entire left subtree 
    inorderDisplay(root->left);
    
    printf("%s %s %d\n", root->monster->name, root->monster->element, root->monster->power);
    // Visit entire right subtree
    inorderDisplay(root->right);
}

// Post-order, the teardown, frees children before releasing node so links stay valid
static void freeTree(BST_Node *root)
{
    // Base case
    if (root == NULL)
    {
        return;
    }
    // Recursively frees left subtree 
    freeTree(root->left);
    // Recursively frees right subtree 
    freeTree(root->right);
    // Frees nodes heap blocks 
    destroyNode(root);
}

int main(void)
{
    BST_Node *root = NULL;     // Tree starts empty, local in main 
    int q;                     // Total number of operations to process
    int i;                     // Loop counter declared before for loop
    int op;                    // Current operation code
    char name[MAXSIZE + 1];    // stack buffer for monster name
    char element[MAXSIZE + 1]; // Stack buffer for element string
    char low[MAXSIZE + 1];     // Stack buffer for lower bound range
    char high[MAXSIZE + 1];    // Stack buffer for the upper bound range
    int power;                 // Temporary stack variable for monster power score

    // Read total operation count Q, exits if input stream is empty
    if (scanf("%d", &q) != 1)
    {
        return 0;
    }

    // Process each of the Q operations sequentially in exact input order
    for (i = 0; i < q; i++)
    {
        // Read the numeric operation code starting this input line
        scanf("%d", &op);

        // Matches to operation case
        switch (op)
        {
            case OP_REGISTER:
                // Read the 3 arguments for Operation 1: name, element, power
                scanf("%s %s %d", name, element, &power);
                // Pre check, decide DUPLICATE before calling malloc()
                if (search(root, name) != NULL)
                {
                    // Report Duplicates
                    printf("DUPLICATE\n");
                }
                else
                {
                    // Absent, allocate 3 blocks, attach leaf, and update root
                    root = insert(root, createNode(name, element, power));
                    printf("INSERTED\n");
                }
                break;

            case OP_REMOVE:
                // Read the target monster name 
                scanf("%s", name);
                // check, verify target exists so deleteNode() conditions holds
                if (search(root, name) == NULL)
                {
                    printf("NOT FOUND\n");
                }
                else
                {
                    // Remove node and capture potentially new root,if the root was deleted
                    root = deleteNode(root, name);
                    printf("DELETED\n");
                }
                break;

            case OP_FIND:
            {
                // Local pointer to hold lookup result
                BST_Node *found;
                // Read target name for operation 3
                scanf("%s", name);
                // Perform O(h) BST lookup
                found = search(root, name);
                if (found == NULL)
                {
                    printf("NOT FOUND\n");
                }
                else
                {
                    printf("FOUND %s %d\n", found->monster->element, found->monster->power);
                }
                break;
            }

            case OP_NEXT:
            {
                // Local pointer 
                BST_Node *next;
                // Read query name 
                scanf("%s", name);
                // Find smallest stored name strictly > query
                next = successor(root, name);
                if (next == NULL)
                {
                    printf("NO SUCCESSOR\n");
                }
                else
                {
                    printf("%s\n", next->monster->name);
                }
                break;
            }

            case OP_RANGE:
                // Read range bounds low -high, for Operation 5
                scanf("%s %s", low, high);
                // Handle reversed range without touching the tree
                if (strcmp(low, high) > 0)
                {
                    printf("0\n");
                }
                else
                {
                    // Run recursive pruned range count and print the integer total
                    printf("%d\n", countRange(root, low, high));
                }
                break;

            case OP_DISPLAY:
                // Check empty tree BEFORE recursion, NULL inside recursion is just a leaf edge
                if (root == NULL)
                {
                    printf("EMPTY\n");
                }
                else
                {
                    // Print stored monsters in alphabetical order
                    inorderDisplay(root);
                }
                break;
        }
    }

    // release every remaining heap block in post-order before exiting
    freeTree(root);
    return 0;
}