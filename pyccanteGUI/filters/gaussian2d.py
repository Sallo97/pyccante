# This file contains the Gauss2DWindow class

import pyccante as pyc
import utils.str_warning as sw
from windows import warningwin as ww
from PySide6.QtWidgets import (QLabel, QPushButton, QLineEdit,
                               QHBoxLayout, QVBoxLayout, QDialog)


class Gauss2DWindow(QDialog):
    def __init__(self, img):
        # Gauss2DWindow is QDialog that
        # implements a window to apply
        # the Gaussian2D filter to an image.
        # img = image to apply the filter to.
        super(Gauss2DWindow, self).__init__()
        self.img = img
        self.setWindowTitle("Gaussian...")

        # Define labels for parameters
        self.sigma_label = QLabel("Sigma: ")

        # Define line edits for parameters
        self.sigma_edit = QLineEdit("0")

        # Put labels and line edits into a layout
        self.sigma_layout = QHBoxLayout()
        self.sigma_layout.addWidget(self.sigma_label)
        self.sigma_layout.addWidget(self.sigma_edit)

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
        self.main_layout.addLayout(self.sigma_layout)
        self.main_layout.addLayout(self.buttons_layout)

    def execute(self):
        # Execute the Conv2D filter to the self.img
        # Modify the self.img with the filtered one.
        try:
            sigma = float(self.sigma_edit.text())
            if sigma > 0:
                new_img = pyc.FilterGaussian2D.execute(self.img, sigma=sigma)
                self.set_img(new_img)
            else:
                # Sigma is not greater than 0.
                # Open a warningwin that warns the user.
                ww.WarningWindow(sw.invalid_sigma_str()).exec()
        except ValueError:
            # One of the typed value is not a number.
            # Open a warningwin that warns the user.
            ww.WarningWindow(sw.invalid_value_str()).exec()

    def set_img(self, new_img):
        # Set the new_img as the current one.
        # new_img = new image to set.
        if new_img is not None:
            self.img = new_img
            self.hide()
        else:
            ww.WarningWindow(sw.invalid_image_str()).exec()
