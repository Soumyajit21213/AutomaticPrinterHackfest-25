// index.js
import express from "express";
import multer from "multer";
import dotenv from "dotenv";
import { v2 as cloudinary } from "cloudinary";
import path from "path";
import { fileURLToPath } from "url";

dotenv.config();

const app = express();
const upload = multer(); // Using memory storage for simplicity

// Get __dirname for ES modules
const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

// Serve static files from the "public" folder
app.use(express.static(path.join(__dirname, "public")));

// Configure Cloudinary with your credentials from environment variables
cloudinary.config({
  cloud_name: process.env.CLOUDINARY_CLOUD_NAME,
  api_key: process.env.CLOUDINARY_API_KEY,
  api_secret: process.env.CLOUDINARY_API_SECRET,
});

// Endpoint to handle signed upload
app.post("/upload", upload.single("file"), async (req, res) => {
  try {
    // Convert the file buffer to a Base64 string (data URI)
    const fileStr = req.file.buffer.toString("base64");
    const dataUri = `data:${req.file.mimetype};base64,${fileStr}`;

    // Upload options: force overwrite by setting public_id and overwrite: true
    const uploadOptions = {
      public_id: "latest_pdf",
      overwrite: true,
      resource_type: "raw", // Use "raw" for PDFs
    };

    // Upload to Cloudinary using signed upload
    cloudinary.uploader.upload(dataUri, uploadOptions, (error, result) => {
      if (error) {
        console.error("Cloudinary error:", error);
        return res.status(500).json({ error: error.message });
      }
      res.json(result);
    });
  } catch (error) {
    console.error("Upload error:", error);
    res.status(500).json({ error: error.message });
  }
});

// Start the server; Replit provides a public URL on process.env.PORT
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
