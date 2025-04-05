document.getElementById("uploadBtn").addEventListener("click", async () => {
    const fileInput = document.getElementById("fileInput");
    const statusMessage = document.getElementById("statusMessage");
  
    if (!fileInput.files.length) {
      statusMessage.innerText = "Please select a file.";
      return;
    }
  
    const file = fileInput.files[0];
    const formData = new FormData();
    formData.append("file", file);
  
    try {
      statusMessage.innerText = "Uploading...";
      // Use your Replit backend URL; Replit sets up a public URL for your Repl
      const response = await fetch("/upload", {  // Relative URL now works!
        method: "POST",
        body: formData,
      });
  
      const data = await response.json();
      if (response.ok) {
        const pdfUrl = data.secure_url;
        statusMessage.innerText = `Upload successful! PDF URL: ${pdfUrl}`;
        console.log("Uploaded PDF URL:", pdfUrl);
        // You can now use this URL for further processing (e.g., convert to image)
      } else {
        throw new Error(data.error);
      }
    } catch (error) {
      statusMessage.innerText = `Upload failed: ${error.message}`;
      console.error("Error during upload:", error);
    }
  });
  