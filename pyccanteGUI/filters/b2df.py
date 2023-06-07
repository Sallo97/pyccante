import pyccante as pyc
import layouts.windows.warningwin as ww
import utils.str_warning as sw
from PySide6.QtWidgets import (QLabel, QPushButton, QLineEdit,
                               QHBoxLayout, QVBoxLayout, QDialog)


class B2DFWindow(QDialog):
    def __init__(self, img, ldr_type):
        self.ldr_type = ldr_type
        self.img = img
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
        # Execute the B2DF filter to the self.img
        # Modify the self.img with the filtered oneì.
        try:
            sigma_s = float(self.sigma_s_line_edit.text())
            sigma_r = float(self.sigma_r_line_edit.text())
            new_img = pyc.FilterBilateral2DF.execute(self.img, sigma_s=sigma_s,
                                                     sigma_r=sigma_r)
            self.img = new_img
            self.hide()
        except ValueError:
            # One of the typed value is not a number.
            # Open a warningwin that warns the user.
            ww.WarningWindow(sw.invalid_value_str()).exec()

    def hide_window(self):
        self.img = None
        self.hide()
