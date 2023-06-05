import pyccante as pyc
from PySide6.QtWidgets import (QLabel, QPushButton, QLineEdit,
                               QHBoxLayout, QVBoxLayout, QDialog)


class B2DFWindow(QDialog):
    def __init__(self, img, ldr_type):
        self.ldr_type = ldr_type
        self.img = self.set_img(img)
        super(B2DFWindow, self).__init__()
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
        self.Cancel_button.clicked.connect(self.hide_window)

        # Put buttons into a layout
        self.buttons_layout = QHBoxLayout()
        self.buttons_layout.addWidget(self.OK_button)
        self.buttons_layout.addWidget(self.Cancel_button)

        # Construct windows
        self.main_layout = QVBoxLayout(self)
        self.main_layout.addLayout(self.sigma_s_layout)
        self.main_layout.addLayout(self.sigma_r_layout)
        self.main_layout.addLayout(self.buttons_layout)

    def execute(self):
        print(f"Inside bd2f with\nself.img= {self.img.nameFile}\nself.ldr_type = {self.ldr_type}")

        sigma_s = float(self.sigma_s_line_edit.text())
        sigma_r = float(self.sigma_r_line_edit.text())
        new_img = pyc.FilterBilateral2DF.execute(self.img, sigma_s=sigma_s,
                                                 sigma_r=sigma_r)
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
        self.img = None
        self.hide()
