# This file contains the B2DFWindow class

import os
import pyccante as pyc
import windows.warningwin as ww
import utils.str_warning as sw
from PySide6.QtWidgets import (QLabel, QPushButton, QLineEdit,
                               QHBoxLayout, QVBoxLayout, QDialog)


class B2DFWindow(QDialog):
    # B2DFWindow is QDialog that
    # implements a window to apply
    # the Bilateral2DF filter to an image.
    def __init__(self, img):
        # img = image to apply the filter to.
        # ldr_flag = determines if the images
        #            has been already normalized
        #            or not.
        super(B2DFWindow, self).__init__()

        # Setting image values
        self.img = img

        # Setting window values
        self.setWindowTitle("Bilateral2DF...")

        # Define labels for parameters
        self.sigma_s_label = QLabel("Sigma_s: ")
        self.sigma_r_label = QLabel("Sigma_r: ")

        # Define line edits for parameters
        self.sigma_s_line_edit = QLineEdit("0")
        self.sigma_r_line_edit = QLineEdit("0")

        # Put labels and line edits into a layout
        self.sigma_s_layout = QHBoxLayout()
        self.sigma_s_layout.addWidget(self.sigma_s_label)
        self.sigma_s_layout.addWidget(self.sigma_s_line_edit)
        self.sigma_r_layout = QHBoxLayout()
        self.sigma_r_layout.addWidget(self.sigma_r_label)
        self.sigma_r_layout.addWidget(self.sigma_r_line_edit)

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
        self.main_layout.addLayout(self.sigma_s_layout)
        self.main_layout.addLayout(self.sigma_r_layout)
        self.main_layout.addLayout(self.buttons_layout)

        # Set window size
        self.setFixedWidth(220)
        self.setFixedHeight(100)

    def execute(self):
        # Execute the B2DF filter to the self.img
        # Modify the self.img with the filtered one.
        try:
            sigma_s = float(self.sigma_s_line_edit.text())
            sigma_r = float(self.sigma_r_line_edit.text())
            self.img.Write("./data/tmp.png", pyc.LDR_type.LT_NONE)
            self.img = pyc.Image("./data/tmp.png", pyc.LDR_type.LT_NOR_GAMMA)
            new_img = pyc.FilterBilateral2DF.execute(self.img, sigma_s=sigma_s,
                                                     sigma_r=sigma_r)
            pyc.denormalize_with_gamma(new_img)

            self.set_img(new_img)

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

