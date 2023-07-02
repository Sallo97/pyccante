# This file contains the RotationWindow class

import pyccante as pyc
import utils.str_warning as sw
from windows import warningwin as ww
from PySide6.QtWidgets import (QLabel, QPushButton, QLineEdit,
                               QHBoxLayout, QVBoxLayout, QDialog)


class RotationWindow(QDialog):
    def __init__(self, img):
        super(RotationWindow, self).__init__()
        # RotationWindow is a QDialog that
        # implements a window to apply
        # the Rotation filter to an image.
        # img = image to apply the filter to.
        self.img = img

        # Setting window parameters
        self.setWindowTitle("Bilateral2DF...")

        # Define labels for parameters
        self.angle_x_label = QLabel("deg X: ")
        self.angle_y_label = QLabel("deg Y: ")
        self.angle_z_label = QLabel("deg Z: ")

        # Define line edits for parameters
        self.angle_x_edit = QLineEdit("0")
        self.angle_y_edit = QLineEdit("0")
        self.angle_z_edit = QLineEdit("0")

        # Put labels and line edits into a layout
        self.angle_x_layout = QHBoxLayout()
        self.angle_x_layout.addWidget(self.angle_x_label)
        self.angle_x_layout.addWidget(self.angle_x_edit)

        self.angle_y_layout = QHBoxLayout()
        self.angle_y_layout.addWidget(self.angle_y_label)
        self.angle_y_layout.addWidget(self.angle_y_edit)

        self.angle_z_layout = QHBoxLayout()
        self.angle_z_layout.addWidget(self.angle_z_label)
        self.angle_z_layout.addWidget(self.angle_z_edit)

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
        self.main_layout.addLayout(self.angle_x_layout)
        self.main_layout.addLayout(self.angle_y_layout)
        self.main_layout.addLayout(self.angle_z_layout)
        self.main_layout.addLayout(self.buttons_layout)

    def execute(self):
        # Execute the Rotation filter
        # Modify the self.img with the filtered one.
        try:
            # get data from the window
            deg_x = float(self.angle_x_edit.text())
            deg_y = float(self.angle_y_edit.text())
            deg_z = float(self.angle_z_edit.text())
            rads = self.convert_angles_rad(deg_x, deg_y, deg_z)

            # apply the filter to a new_image
            new_img = pyc.FilterRotation.execute(self.img, rads[0],
                                                 rads[1], rads[2])
            # set the filtered image as the main one
            self.set_img(new_img)
        except ValueError:
            # One of the typed value is not a number.
            # Open a warningwin that warns the user.
            ww.WarningWindow(sw.invalid_value_str()).exec()

    def convert_angles_rad(self, x, y, z):
        # FilterRotations interprets it's values as rad,
        # but the inputted ones are in deg.
        # So before giving them to the filter it is
        # necessary to convert them
        rad_x = x * 0.0175
        rad_y = y * 0.0175
        rad_z = z * 0.0175
        return [rad_x, rad_y, rad_z]

    def set_img(self, new_img):
        # Set the new_img as the current one.
        # new_img = new image to set.
        if new_img is not None:
            self.img = new_img
            self.hide()
        else:
            ww.WarningWindow(sw.invalid_image_str()).exec()