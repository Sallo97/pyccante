# This file contains the B2DFWindow class

import pyccante as pyc
import windows.warningwin as ww
import utils.str_warning as sw
from bars import file as fl
from PySide6.QtWidgets import (QLabel, QPushButton, QLineEdit,
                               QHBoxLayout, QVBoxLayout, QFileDialog, QDialog)


class B2DSWindow(QDialog):
    # B2DSWindow is QDialog that
    # implements a window to apply
    # the Bilateral2DS filter to an image.
    def __init__(self, img, ldr_type):
        # img = image to apply the filter to.
        # ldr_type = ldr_type of the image.
        super(B2DSWindow, self).__init__()

        # Setting image values
        self.ldr_type = ldr_type
        self.img = img
        self.img_edge = None

        # Setting up window
        self.setWindowTitle("Bilateral2DS...")

        # Define labels for parameters
        self.imgEdge_label = QLabel("Image Edge: ")
        self.sigma_s_label = QLabel("Sigma_s: ")
        self.sigma_r_label = QLabel("Sigma_r: ")

        # Define button for imgEdge
        self.imgEdge_button = QPushButton("Open...")
        self.imgEdge_button.clicked.connect(self.open_imgedge)

        # Define line edits for parameters
        self.sigma_s_line_edit = QLineEdit("0")
        self.sigma_r_line_edit = QLineEdit("0")

        # Put labels and line edits into a layout
        self.imgEdge_label_layout = QHBoxLayout()
        self.imgEdge_label_layout.addWidget(self.imgEdge_label)
        self.imgEdge_label_layout.addWidget(self.imgEdge_button)

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
        self.main_layout.addLayout(self.imgEdge_label_layout)
        self.main_layout.addLayout(self.sigma_s_layout)
        self.main_layout.addLayout(self.sigma_r_layout)
        self.main_layout.addLayout(self.buttons_layout)

        # Set window size
        self.setFixedWidth(220)
        self.setFixedHeight(120)

    def execute(self):
        # Execute the B2DF filter to the self.img
        # Modify the self.img with the filtered one.
        try:
            sigma_s = float(self.sigma_s_line_edit.text())
            sigma_r = float(self.sigma_r_line_edit.text())

            # Check in which case we are:
            # 1) The user has selected an image edge
            # 2) The user has not selected an image edge
            if self.img_edge is not None:
                # Case in which the user has selected an image edge
                new_img = pyc.FilterBilateral2DS.execute(self.img, imgEdge=self.img_edge,
                                                         sigma_s=sigma_s, sigma_r=sigma_r)
            else:
                # Case in which the user has not selected an image edge
                new_img = pyc.FilterBilateral2DS.execute(self.img, sigma_s=sigma_s,
                                                         sigma_r=sigma_r)

            # Set the filtered image as the main image
            self.set_img(new_img)

        except ValueError:
            # One of the typed value is not a number.
            # Open a warningwin that warns the user.
            ww.WarningWindow(sw.invalid_value_str()).exec()

    def open_imgedge(self):
        # Opens a file dialog to select the img_edge image
        # save the image in self.weight
        path = QFileDialog.getOpenFileName(
            self,
            "Open Image Edge",
            "./data",
            "Image Files (*.png *.jpg *.hdr)")
        self.img_edge = fl.read_img(path[0])
        name_file = path[0].split("/")
        self.imgEdge_button.setText(f"{name_file[-1]}")

    def set_img(self, new_img):
        # Set the new_img as the current one.
        # new_img = new image to set.
        if new_img is not None:
            self.img = new_img
            self.hide()
        else:
            ww.WarningWindow(sw.invalid_image_str()).exec()
