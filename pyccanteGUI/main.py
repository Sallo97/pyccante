import sys
import pyccante as pyc
from PySide6.QtWidgets import (QApplication, QDialog, QPushButton,
                               QLineEdit, QVBoxLayout, QTableWidget, QTableWidgetItem)


class Form(QDialog):
    def __init__(self, parent=None):
        super(Form, self).__init__(parent)
        self.categories = {"Filters": ["Luminance", "Bilateral2df", "Bilateral2ds", "Conv2D", "Max", "Mean", "Med",
                                       "MedVec", "Mosaic", "Warp2D", "Rotation"],
                           "Algorithms": ["HDRMerger", "GrowCut", "PoissonSolver", "ConnectedComponents"],
                           "ToneMapping": ["Ward Histogram TMO", "Reinhard TMO", "Exposure Fusion", "Durand TMO",
                                           "Drago TMO"]}

        self.img = pyc.Image()
        self.setWindowTitle("Pyccante GUI")

        # Define tree
        self.table = QTableWidget()
        self.table.setRowCount(len(self.categories.get("Filters")))
        self.table.setColumnCount(3)
        self.table.setHorizontalHeaderLabels(["Filter", "Algorithms", "Tone Mapping"])
        self.construct_table()

        # Define box to write
        self.edit = QLineEdit("Image path here.")

        # Define buttons
        self.read_button = QPushButton("Read Image")
        self.copy_button = QPushButton("Copy Image")

        # Add button signal to greetings slot
        self.read_button.clicked.connect(self.read_img)
        self.copy_button.clicked.connect(self.copy_img)

        layout = QVBoxLayout(self)
        layout.addWidget(self.edit)
        layout.addWidget(self.read_button)
        layout.addWidget(self.copy_button)
        layout.addWidget(self.table)

    def construct_table(self):
        i = 0
        for i, (key, values) in enumerate(self.categories.items()):
            for j, value in enumerate(values):
                item_name = QTableWidgetItem(value)
                self.table.setItem(j, i, item_name)

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
