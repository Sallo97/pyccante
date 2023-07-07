# This file contains the Conv2DWindow class

import os
import pyccante as pyc
import utils.str_warning as sw
from windows import warningwin as ww
from PySide6.QtWidgets import (QLabel, QPushButton,
                               QHBoxLayout, QVBoxLayout,
                               QFileDialog, QDialog)


class Conv2DWindow(QDialog):
    # Conv2DWindow is QDialog that
    # implements a window to apply
    # the Conv2D filter to an image.
    def __init__(self, img):
        # img = image to apply the filter to.
        # ldr_type = ldr_type of the image.
        super(Conv2DWindow, self).__init__()

        # Setting image values
        self.img = img

        self.conv = None

        # Setting up window
        self.setWindowTitle("Conv2D...")

        # Define labels for parameters
        self.conv_label = QLabel("Conv: ")

        # Define button for imgEdge
        self.conv_button = QPushButton("Open...")
        self.conv_button.clicked.connect(self.open_conv)

        # Put labels and line edits into a layout
        self.conv_layout = QHBoxLayout()
        self.conv_layout.addWidget(self.conv_label)
        self.conv_layout.addWidget(self.conv_button)

        # Define buttons
        self.OK_button = QPushButton("OK")
        self.Cancel_button = QPushButton("Cancel")
        self.OK_button.clicked.connect(self.execute)
        self.Cancel_button.clicked.connect(self.hide)

        # Put buttons into a layout
        self.buttons_layout = QHBoxLayout()
        self.buttons_layout.addWidget(self.OK_button)
        self.buttons_layout.addWidget(self.Cancel_button)

        # Construct windows
        self.main_layout = QVBoxLayout(self)
        self.main_layout.addLayout(self.conv_layout)
        self.main_layout.addLayout(self.buttons_layout)

        # Set window size
        self.setFixedWidth(220)
        self.setFixedHeight(100)

    def execute(self):
        # Execute the Conv2D filter to the self.img
        # Modify the self.img with the filtered one.

        self.img.Write("./data/tmp.png", pyc.LDR_type.LT_NONE)
        self.img = pyc.Image("./data/tmp.png", pyc.LDR_type.LT_NOR_GAMMA)

        pyc.conv_normalization(self.conv)
        new_img = pyc.FilterConv2D.execute(self.img, conv=self.conv)

        # Set the filtered image as the main image
        pyc.denormalize_with_gamma(new_img)
        self.set_img(new_img)

    def open_conv(self):
        # Opens a file dialog to select the img_edge image
        # save the image in self.weight
        path = QFileDialog.getOpenFileName(
            self,
            "Open Conv",
            "./data",
            "Image Files (*.ppm *.pgm *.tga *.png *.jpg *.bmp *.hdr *.exr)")
        if path[0] != '':
            self.conv = pyc.Image(path[0], pyc.LDR_type.LT_NOR_GAMMA)
            name_file = path[0].split("/")
            self.conv_button.setText(f"{name_file[-1]}")

    def set_img(self, new_img):
        # Set the new_img as the current one.
        # new_img = new image to set.
        if new_img is not None:
            self.img = new_img
            self.hide()
        else:
            ww.WarningWindow(sw.invalid_image_str()).exec()
