from PIL import Image

def ReadOneImage(image_path):
  with Image.open(image_path) as img:
    img.show()
  
