import sys
import pyccante as pyc
from PySide6.QtWidgets import (QApplication, QDialog, QPushButton,
                               QLineEdit, QVBoxLayout)


class Form(QDialog):
    def __init__(self, parent=None):
        super(Form, self).__init__(parent)
        self.img = pyc.Image()
        self.setWindowTitle("Pyccante GUI")
        self.edit = QLineEdit("Image path here.")
        self.read_button = QPushButton("Read Image")
        self.copy_button = QPushButton("Copy Image")

        # Add button signal to greetings slot
        self.read_button.clicked.connect(self.read_img)
        self.copy_button.clicked.connect(self.copy_img)

        layout = QVBoxLayout(self)
        layout.addWidget(self.edit)
        layout.addWidget(self.read_button)
        layout.addWidget(self.copy_button)

    def read_img(self):
        print(f"Reading the image {self.edit.text()}...")
        self.img = pyc.Image(self.edit.text(), pyc.LDR_type.LT_NONE)
        if self.img.isValid():
            print("The image has been read")
        else:
            print("The namefile doesn't exist!")

    def copy_img(self):
        print(f"Copying {self.edit.text()}...")
        name_img = self.img.nameFile.split(".")
        self.img.Write(f"{name_img[0]}_copy.{name_img[1]}", pyc.LDR_type.LT_NONE)
        print("The image has been copied!")


if __name__ == '__main__':
    # Create a Qt Application
    app = QApplication(sys.argv)

    # Create and show the form
    form = Form()
    form.show()

    # Run the main Qt loop
    sys.exit(app.exec())
