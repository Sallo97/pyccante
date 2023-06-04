# This file contains static methods that returns the prefixed path
# for the base imgs of the Pyccante GUI

def get_plc_path():
    # This path refers to the default image of the GUI
    return "./data/placeholder.png"


def get_hdr_path():
    # When the GUI loads an HDR-Image, the user see in reality
    # a tone-mapped .png of the original image. This is the
    # path where this temporary image is found.
    return "./data/_hdr_temp.png"

def get_custom_path():
    # When the GUI apply action to a loaded image, this actions are
    # not applyed to the original image, but a custom one, this is the
    # path where this temporary image is found.
    return "./data/_custom_temp.png"