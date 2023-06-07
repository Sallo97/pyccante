import pyccante as pyc
import layouts.windows.warningwin as ww
import utils.str_warning as sw
from bars import file as fl
from PySide6.QtWidgets import (QLabel, QPushButton, QLineEdit,
                               QHBoxLayout, QVBoxLayout, QFileDialog, QDialog)


class B2DSWindow(QDialog):
    def __init__(self, img, ldr_type):
        self.ldr_type = ldr_type
        self.img = self.set_img(img)
        self.imgedge = None
        super(B2DSWindow, self).__init__()
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
        self.Cancel_button.clicked.connect(self.hide_window)

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

    def execute(self):
        try:
            sigma_s = float(self.sigma_s_line_edit.text())
            sigma_r = float(self.sigma_r_line_edit.text())
            if self.imgedge is not None:
                new_img = pyc.FilterBilateral2DS.execute(self.img, imgEdge=self.imgedge,
                                                     sigma_s=sigma_s, sigma_r=sigma_r)
            else:
                new_img = pyc.FilterBilateral2DS.execute(self.img, sigma_s=sigma_s,
                                                     sigma_r=sigma_r)
            self.img = new_img
            self.hide()
        except ValueError:
            # One of the typed value is not a number.
            # Open a warningwin that warns the user.
            ww.WarningWindow(sw.invalid_value_str()).exec()

    def open_imgedge(self):
        path = QFileDialog.getOpenFileName(
            self,
            "Open Image Edge",
            "./data",
            "Image Files (*.png *.jpg *.hdr)")
        self.imgedge = fl.read_img(path[0])
        name_file = path[0].split("/")
        self.imgEdge_button.setText(f"{name_file[-1]}")

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
        self.img = None
        self.hide()
