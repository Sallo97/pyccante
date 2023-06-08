# This file contains static methods to read and write images.

import pyccante as pyc
import os


def read_img(path):
    # Loads a pyccante image from a path
    # path = path to the image

    # Creating the image
    new_img = pyc.Image(path, pyc.LDR_type.LT_NONE)

    # Checking if the image is valid
    if new_img.isValid():
        print("The image has been read")
        return new_img
    else:
        print("The image is not valid!")
        return None


def save_img(img, img_path, ldr_type):
    # Saves a pyccante image in a path
    # img = image to save
    # img_path = path to save the image
    # ldr_type = the ldr_type
    img.Write(f"{img_path[0]}{img_path[1]}", ldr_type)


def remove_temp_images():
    # Removes all the temp images
    # that are created during the execution
    if os.path.isfile("./data/_custom_temp.png"):
        os.remove("./data/_custom_temp.png")
    if os.path.isfile("./data/_hdr_temp.png"):
        os.remove("./data/_hdr_temp.png")
