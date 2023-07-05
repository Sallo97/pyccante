# This file contains the RotationWindow class

import pyccante as pyc
import numpy as np
import utils.str_warning as sw
from windows import warningwin as ww
from PySide6.QtWidgets import (QLabel, QPushButton, QHBoxLayout,
                               QLineEdit, QVBoxLayout, QDialog,
                               QCheckBox, QGridLayout)
from PySide6.QtCore import Qt


class Warp2DWindow(QDialog):
    def __init__(self, img):
        super(Warp2DWindow, self).__init__()
        self.img = img
        self.setWindowTitle("Warp2D...")

        # Define labels for parameters
        self.mtx_label = QLabel("Matrix: ")

        # Define line edits for parameters
        self.r1c1_edit = QLineEdit("0")
        self.r1c2_edit = QLineEdit("0")
        self.r1c3_edit = QLineEdit("0")

        self.r2c1_edit = QLineEdit("0")
        self.r2c2_edit = QLineEdit("0")
        self.r2c3_edit = QLineEdit("0")

        self.r3c1_edit = QLineEdit("0")
        self.r3c2_edit = QLineEdit("0")
        self.r3c3_edit = QLineEdit("0")

        # Put row and mtx edit together
        self.rc_layout = QGridLayout()

        # Define first row of matrix
        self.rc_layout.addWidget(self.r1c1_edit, 0, 0)
        self.rc_layout.addWidget(self.r1c2_edit, 0, 1)
        self.rc_layout.addWidget(self.r1c3_edit, 0, 2)

        # Define second row of matrix
        self.rc_layout.addWidget(self.r2c1_edit, 1, 0)
        self.rc_layout.addWidget(self.r2c2_edit, 1, 1)
        self.rc_layout.addWidget(self.r2c3_edit, 1, 2)

        # Define third row of matrix
        self.rc_layout.addWidget(self.r3c1_edit, 2, 0)
        self.rc_layout.addWidget(self.r3c2_edit, 2, 1)
        self.rc_layout.addWidget(self.r3c3_edit, 2, 2)

        # Define mtx
        self.mtx_layout = QHBoxLayout()
        self.mtx_layout.addWidget(self.mtx_label)
        self.mtx_layout.addLayout(self.rc_layout, stretch=1)

        # Define checkboxes
        self.size = QCheckBox("Same size")
        self.cntr = QCheckBox("Centroid")
        self.checks = QHBoxLayout()
        self.checks.addWidget(self.size)
        self.checks.addWidget(self.cntr)
        self.checks.setAlignment(Qt.AlignmentFlag.AlignHCenter)

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
        self.main_layout.addLayout(self.mtx_layout)
        self.main_layout.addLayout(self.checks)
        self.main_layout.addLayout(self.buttons_layout)

        # Set window size
        self.setFixedWidth(220)
        self.setFixedHeight(150)

    def execute(self):
        try:
            same_size = self.size.isChecked()
            centroid = self.cntr.isChecked()
            mtx = self.create_mtx()
            if mtx.determinant() > 0:
                new_img = pyc.FilterWarp2D.execute(self.img, h=mtx,
                                                   bSameSize=same_size, bCentroid=centroid)
                self.set_img(new_img)
            else:
                # The mtx has a negative determinant,
                # cannot execute the filter.
                ww.WarningWindow(sw.invalid_mtx_str()).exec()
        except ValueError:
            # One of the typed value is not a number.
            # Open a warningwin that warns the user.
            ww.WarningWindow(sw.invalid_value_str()).exec()

    def create_mtx(self):
        # Returns a Matrix3x3 with the inputted values
        # by the user.
        mtx = np.array([float(self.r1c1_edit.text()), float(self.r1c2_edit.text()), float(self.r1c3_edit.text()),
                        float(self.r2c1_edit.text()), float(self.r2c2_edit.text()), float(self.r2c3_edit.text()),
                        float(self.r3c1_edit.text()), float(self.r3c2_edit.text()), float(self.r3c3_edit.text())],
                       np.float32)

        mtx3x3 = pyc.Matrix3x3(mtx)
        return mtx3x3

    def set_img(self, new_img):
        # Set the new_img as the current one.
        # new_img = new image to set.
        if new_img is not None:
            self.img = new_img
            self.hide()
        else:
            ww.WarningWindow(sw.invalid_image_str()).exec()
