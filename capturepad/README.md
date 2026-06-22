# CapturePad

**iPad-first CRUD system with powerful camera capture, barcode/QR scanning, and vision processing extensions.**

Turn your iPad into a field data collection + structured records machine. Create records, attach rich photos taken directly with the iPad camera, scan barcodes and QR codes live, then use local on-device extensions to turn images and codes into usable structured data.

---

## Features

### Core CRUD
- **Create, Read, Update, Delete** entries
- Clean Apple-style UI with large touch targets optimized for iPad
- Fields: Title, Category, Value/Quantity, Description/Notes
- Categories: Equipment, Sample, Document, Receipt, Location, Other
- Full-text search + category filter
- Sort by most recently updated

### Camera + Barcode Extensions (iPad native)
- **Live Camera** — Uses `getUserMedia` for in-app camera preview + shutter
- **Scan Barcode / QR** — Full support for 1D barcodes and QR codes using @zxing/library (live camera scanning)
- **Native Camera Fallback** — Works reliably via `<input capture="environment">` when needed
- **Library upload** supported — you can scan codes from existing photos too
- Attach any number of photos to records
- Codes are stored on records (`codes[]` array) and shown in descriptions + badges
- Scan directly from the entry editor ("Scan Code" button) or from the Process tab
- Manual code entry fallback always available
- Photos stored locally (as high-quality JPEG data URLs)

### Vision Processing Extensions
Open any photo (attached or standalone) and run:

| Extension         | What it does                              |
|-------------------|-------------------------------------------|
| OCR (Tesseract)   | Extracts text from photo → copy or apply to entry description |
| Image Stats       | Dimensions, pixel count, average color (with swatch) + aspect ratio |
| Grayscale         | Convert photo to black & white            |
| High-Contrast     | Threshold filter (great for documents)    |
| Sharpen           | Light unsharp mask                        |
| New Entry         | Instantly create a record from the processed photo |

All vision processing runs **locally on your iPad** (Tesseract.js downloads language data once).

### Data Management
- Persistent via localStorage + embedded photos
- **Export** entire database as JSON (includes all photos)
- **Import** (replace or merge)
- Sample data on first launch

### iPad & PWA Ready
- Safe area insets support
- Large tappable targets (≥48px)
- Works in Safari, can be **Added to Home Screen**
- Portrait and landscape friendly
- Keyboard shortcuts (`/` to search, `Cmd+N` to create, `Esc` to close)
- Responsive grid (excellent on iPad Pro)

---

## How to Use on iPad

1. Open the folder in your code environment or copy `index.html` + `manifest.json` to your iPad (AirDrop, Files, etc.).
2. Open `index.html` in **Safari**.
3. Tap the **Share** button → **Add to Home Screen**.
4. Launch from the home screen icon for full-screen PWA experience.

### Recommended Workflow

**Quick field capture:**
1. Switch to **Capture** tab
2. Frame your subject with live camera
3. Tap **TAKE PHOTO** or **SCAN BARCODE / QR**
4. Choose to create a new entry automatically or attach to existing one

**Barcode / QR scanning:**
- Use the big green **SCAN BARCODE / QR** button in the Capture tab (live continuous scanning)
- Use **Scan Code** inside any entry editor (adds directly to the record)
- In **Process** tab after loading a photo: click **Detect Barcode / QR**
- Works with camera or previously taken photos
- Supports most common formats (QR, EAN/UPC, Code 128, Code 39, Data Matrix, etc.)

**Turn a photo into data:**
1. In **Process** tab (or tap a photo → "Process this photo")
2. Click **Run OCR (Extract Text)** or **Detect Barcode / QR**
3. Tap **Create Entry from this Code** (or text) to auto-populate a record

**Photo-enhanced record editing:**
- In the entry editor you can tap **Take Photo** for live capture directly into the record
- Multiple photos supported per entry

---

## Running Locally (Development)

```bash
# From inside capturepad folder
python3 -m http.server 8080
# or
npx serve .
```

Then open http://localhost:8080 in Safari or your desktop browser (desktop works too).

---

## Technical Notes

- **Single-file** architecture: everything is in `index.html` (Tailwind via CDN).
- **Tesseract.js** is loaded from CDN. First OCR run downloads ~10–15 MB of language data (cached by browser afterward).
- If offline or Tesseract fails to load, OCR gracefully falls back to realistic simulated results for demos.
- Photos are stored as JPEG data URLs. For large numbers of high-res photos consider periodic export + clearing older entries.
- No backend required — 100% client-side.

---

## Data Model (for reference)

```js
{
  id: string,
  title: string,
  category: string,
  description: string,
  value: number | null,
  photos: [{ id, dataUrl, timestamp }],
  created: ISOString,
  updated: ISOString
}
```

---

## Keyboard Shortcuts

| Shortcut       | Action             |
|----------------|--------------------|
| `/`            | Focus search       |
| `Cmd/Ctrl + N` | New entry          |
| `Esc`          | Close modals / leave Capture |

---

## Limitations & Future Ideas

- Local storage quotas apply (typically 5–50 MB depending on browser).
- No multi-device sync (easy to add via optional backend later).
- OCR works best with clear printed text. Handwriting support varies.

Ideas for extensions you can add:
- Barcode / QR scanning (jsQR or Barcode Detection API)
- Dominant color palette extraction
- Basic object counting via canvas
- CSV export
- Templates for common form types

---

Built for iPad workflows — fast, private, offline-first. 
