import sys
import os
from bars import menu_bar
from layouts import info, lines, sliders as sls
from layouts.windows import mainwin as mw, customwin as cw
from PySide6.QtWidgets import (QApplication, QVBoxLayout, QHBoxLayout,
                               QLabel, QFrame, QMainWindow, QSizePolicy)
from PySide6.QtGui import QIcon
from PySide6.QtCore import Qt


def remove_temp_images():
    if os.path.isfile("./data/_custom_temp.png"):
        os.remove("./data/_custom_temp.png")
    if os.path.isfile("./data/_hdr_temp.png"):
        os.remove("./data/_hdr_temp.png")


def construct_boxes(boxes, categories):
    for i, (key, values) in enumerate(categories.items()):
        boxes[i].addItem(f"Select the {key} you want to apply...")
        for value in values:
            boxes[i].addItem(value)


class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()

        # ImageWindows size values
        main_h = 170
        main_w = 170

        custom_h = 600
        custom_w = 600

        # Configure Window bar parameters
        self.setWindowTitle("Pyccante GUI [no image loaded]")
        self.setWindowIcon(QIcon("./data/icon.png"))

        # Define info layout
        self.info_frame = info.InfoFrame()

        # Define images windows
        self.main_win = mw.MainImgWindow(main_w, main_h, self.info_frame)
        self.custom_win = cw.CustomImgWindow(custom_w, custom_h, None)

        # Construct menus
        menubar = menu_bar.MenuBarWindow(self.main_win, self.custom_win, self)

        # Define History

        # Define layout sx
        self.sx_layout = QVBoxLayout()
        self.sx_layout.addWidget(self.main_win)
        self.sx_layout.addWidget(lines.get_h_line())
        self.sx_layout.addWidget(sls.SlidersFrame(self.main_win, self.custom_win))
        self.sx_layout.addWidget(lines.get_h_line())
        self.sx_layout.addWidget(self.info_frame)
        self.sx_layout.setAlignment(Qt.AlignmentFlag.AlignTop)

        # sx_layout + v line
        sx_v = QHBoxLayout()
        sx_v.addLayout(self.sx_layout)
        sx_v.addWidget(lines.get_v_line())

        # Define frame sx
        sx_frame = QFrame()
        sx_frame.setLayout(sx_v)
        sx_frame.setFixedWidth(200)

        # Construct main windows
        self.main_layout = QHBoxLayout()
        self.main_layout.setMenuBar(menubar)
        self.main_layout.addWidget(sx_frame)
        self.main_layout.addWidget(self.custom_win)

        # Construct main widget
        main_widget = QLabel()
        main_widget.setMinimumSize(900, 700)
        main_widget.setLayout(self.main_layout)
        main_widget.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Fixed)

        # Set main windows
        self.setCentralWidget(main_widget)

    def update_window_title(self, text):
        self.setWindowTitle(f"Pyccante GUI [{text}]")


if __name__ == '__main__':

    # Create a Qt Application
    app = QApplication(sys.argv)

    # Create and show the form
    main_window = MainWindow()
    main_window.show()

    # Run the main Qt loop
    app.exec()

    # Deleting all the temp images
    print("Closing...")
    remove_temp_images()

    # Closing the program
    sys.exit()
