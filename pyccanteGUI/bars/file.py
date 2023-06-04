import pyccante as pyc


def read_img(path):
    # Creating the image
    print(f"Inside read_img with path = {path}")
    new_img = pyc.Image(path, pyc.LDR_type.LT_NONE)

    # Checking if the image is valid
    if new_img.isValid():
        print("The image has been read")
        return new_img
    else:
        print("The image is not valid!")
        return None


def save_img(img, img_path, ldr_type):
    # Writing the image
    img.Write(f"{img_path[0]}{img_path[1]}", ldr_type)
