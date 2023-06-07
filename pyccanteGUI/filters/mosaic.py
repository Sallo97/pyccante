import pyccante as pyc
from utils import str_path
from PySide6.QtWidgets import (QLabel, QPushButton, QHBoxLayout,
                               QVBoxLayout, QDialog)


class MosaicWindow(QDialog):
    def __init__(self, img, ldr_type):
        super(MosaicWindow, self).__init__()
        self.ldr_type = ldr_type
        self.img = self.set_img(img)
        self.setWindowTitle("Mosaic...")

        # Define labels for parameters
        self.ask_label = QLabel("Apply the Filter?")

        # Define buttons
        self.OK_button = QPushButton("OK")
        self.Cancel_button = QPushButton("Cancel")
        self.OK_button.clicked.connect(self.execute)
        self.Cancel_button.clicked.connect(self.hide_window)

        # Put buttons into a layout
        self.buttons_layout = QHBoxLayout()
        self.buttons_layout.addWidget(self.OK_button)
        self.buttons_layout.addWidget(self.Cancel_button)

        # Construct windows
        self.main_layout = QVBoxLayout(self)
        self.main_layout.addWidget(self.ask_label)
        self.main_layout.addLayout(self.buttons_layout)

    def execute(self):
        print(f"executing mosaic with\nself.img = {self.img}")

        new_img = pyc.FilterMosaic.execute(self.img)
        if new_img is not None:
            self.img = new_img
        self.hide()

    def set_img(self, img):
        # This method set the image to be filtered.
        # The image must be reloaded because we need
        # to apply the most recent ldr_type.
        # img = the image to be filtered

        # Checking if the image has not been modified yet
        if img.nameFile != ' ':
            return pyc.Image(img.nameFile, self.ldr_type)
        else:
            # In case the image has been already modified, the path
            # is empty, so we get the image from the tmp custom file
            return pyc.Image(img.customPath, self.ldr_type)

    def hide_window(self):
        # Since we need to load the image from the temp file
        # and not using the original image, in case we exit
        # doing nothing, it is necessary to set the image at None
        # before hiding the windows.
        # If it is not done, we will pass a full "empty" image to
        # the img_window will, causing a bug
        self.img = None
        self.hide()
