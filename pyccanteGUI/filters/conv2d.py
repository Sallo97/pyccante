import pyccante as pyc
import utils.str_warning as sw
from layouts.windows import warningwin as ww
from bars import file as fl
from PySide6.QtWidgets import (QLabel, QPushButton,
                               QHBoxLayout, QVBoxLayout,
                               QFileDialog, QDialog)


class Conv2DWindow(QDialog):
    def __init__(self, img, ldr_type):
        super(Conv2DWindow, self).__init__()
        self.ldr_type = ldr_type
        self.img = self.set_img(img)
        self.conv = None
        self.war_win = ww.WarningWindow("You didn't select an image for conv!"
                                        "\nThe filter was not applied.")
        self.setWindowTitle("Conv2D...")

        # Define labels for parameters
        self.conv_label = QLabel("Conv: ")

        # Define button for imgEdge
        self.conv_button = QPushButton("Open...")
        self.conv_button.clicked.connect(self.open_conv)

        # Put labels and line edits into a layout
        self.conv_layout = QHBoxLayout()
        self.conv_layout.addWidget(self.conv_label)
        self.conv_layout.addWidget(self.conv_button)

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
        self.main_layout.addLayout(self.conv_layout)
        self.main_layout.addLayout(self.buttons_layout)

    def execute(self):
        if self.conv_condition():
            new_img = pyc.FilterConv2D.execute(self.img, conv=self.conv)
            if new_img is not None:
                self.img = new_img
                self.hide()

    def conv_condition(self):
        # Checks if the conv image as been inputted
        # and if it's the same size as the read image.
        # Returns true if both conditions are valid,
        # false otherwise
        if self.conv is not None:
            if self.conv.size() == self.img.size():
                return True
            else:
                ww.WarningWindow(sw.invalid_size_str()).exec()
        else:
            ww.WarningWindow(sw.missing_images_str()).exec()
        return False

    def open_conv(self):
        path = QFileDialog.getOpenFileName(
            self,
            "Open Conv",
            "./data",
            "Image Files (*.png *.jpg *.hdr)")
        self.conv = fl.read_img(path[0])
        name_file = path[0].split("/")
        self.conv_button.setText(f"{name_file[-1]}")

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
