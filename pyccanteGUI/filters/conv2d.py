import pyccante as pyc
import imgwindow as iw
import warningwin as ww
from menubar import file as fl
from PySide6.QtWidgets import (QLabel, QPushButton,
                               QHBoxLayout, QVBoxLayout,
                               QFileDialog, QDialog)


class Conv2DWindow(QDialog):
    def __init__(self, img, path, win, ldr_type):
        super(Conv2DWindow, self).__init__()
        self.img = img
        self.conv = None
        self.path = path
        self.win = win
        self.modified = False
        self.ldr_type = ldr_type
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

        # Construct window
        self.main_layout = QVBoxLayout(self)
        self.main_layout.addLayout(self.conv_layout)
        self.main_layout.addLayout(self.buttons_layout)

    def execute(self):

        new_img = pyc.Image(self.img.nameFile, self.ldr_type)
        if self.conv is not None:
            new_img = pyc.FilterConv2D.execute(img=new_img, conv=self.conv)
            if new_img is not None:
                self.img = new_img
                self.img.Write(self.path, self.ldr_type)
                # iw.update_pixmap(self.win, self.path)
                self.modified = True
            self.hide_window()
        else:
            self.war_win.exec()

    def hide_window(self):
        self.conv_button.setText("Open...")
        self.conv = None
        self.hide()

    def update_infos(self, img, path, win, ldr_type):
        self.img = img
        self.path = path
        self.win = win
        self.ldr_type = ldr_type

    def open_conv(self):
        path = QFileDialog.getOpenFileName(
            self,
            "Open Conv",
            "./data",
            "Image Files (*.png *.jpg *.hdr)")
        self.conv = fl.read_img(path[0], None, None)
        name_file = path[0].split("/")
        self.conv_button.setText(f"{name_file[-1]}")
