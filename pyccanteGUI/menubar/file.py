import pyccante as pyc
import imgwindow as iw
from PySide6.QtWidgets import (QFileDialog)


def read_img(path, main_win = None, custom_win = None):
    # Creating the image
    print(f"Reading the image {path}")
    new_img = pyc.Image(path, pyc.LDR_type.LT_NONE)

    # Checking if the image is valid
    if new_img.isValid():
        print("The image has been read")

        # Check if the image is hdr or ldr
        path = check_img_ext(new_img, path)

        if main_win is not None and custom_win is not None:
            # Apply the image to the main and custom window
            main_win.update_pixmap(new_img.width, new_img.height, path)
            custom_win.update_pixmap(new_img.width, new_img.height, path)
        return new_img
    else:
        print("The image is not valid!")
        return None


def save_img(img, img_path, ldr_type):
    # Writing the image
    img.Write(f"{img_path[0]}{img_path[1]}", ldr_type)


def check_img_ext(img, path):
    name_img = img.nameFile.split(".")
    if name_img[1] == "hdr":
        print("The image is an hdr image, using the default Tone Mapper")
        tmo_img = pyc.ReinhardTMO.executeGlobal1(img)
        tmo_img.Write("./data/_hdr_temp.png", pyc.LDR_type.LT_NOR)
        return "./data/_hdr_temp.png"
    return path
