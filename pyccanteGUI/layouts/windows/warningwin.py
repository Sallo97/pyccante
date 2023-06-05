# This file contains the class WarningWindow.
# WarningWindow offers a QDialog used to give a warning
# to a user regarding the issue specified when the object
# is constructed.

from PySide6.QtWidgets import (QLabel, QPushButton,
                               QVBoxLayout, QDialog)


class WarningWindow(QDialog):
    def __init__(self, text):
        # text = The text shown when the warning is launched
        super(WarningWindow, self).__init__()
        self.text = text
        self.setWindowTitle("OOPPS!")

        # Define label for text
        self.text_label = QLabel(self.text)

        # Define Ok button
        self.OK_button = QPushButton("OK")
        self.OK_button.clicked.connect(self.hide)

        # Construct windows
        self.main_layout = QVBoxLayout(self)
        self.main_layout.addWidget(self.text_label)
        self.main_layout.addWidget(self.OK_button)
