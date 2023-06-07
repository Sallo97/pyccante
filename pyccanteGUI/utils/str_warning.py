# This file contains static methods that returns one of the possibile
# warning messages that can be shown during the execution of the program.

def invalid_value_str():
    return "Invalid value, only numbers are accepted!"


def missing_images_str():
    return "One or more images aren't inputted"


def invalid_size_str():
    return "Input image(s) must have the same size as the read one!"


def invalid_mtx_str():
    return "The determinant is negative!\nTry again with another matrix."
