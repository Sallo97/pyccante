# This file contains the MainWindow class, which is the main window of the GUI.

import sys
from bars import menu_bar, file
from layouts import info, sliders as sls
from utils import lines
from windows import readwin as mw, customwin as cw
from PySide6.QtWidgets import (QApplication, QVBoxLayout, QHBoxLayout,
                               QLabel, QFrame, QMainWindow, QSizePolicy)
from PySide6.QtGui import QIcon
from PySide6.QtCore import Qt


class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        # The MainWindow class is the main window of the GUI.
        # It contains the main layout and the menu bar.

        # Set base paramateres for the image windows
        main_h = 170    # Height of the main image window
        main_w = 170    # Width of the main image window

        custom_h = 600  # Height of the custom image window
        custom_w = 600  # Width of the custom image window

        # Define info layout
        self.info_frame = info.InfoFrame()

        # Define images windows
        self.preview_read_win = mw.ReadWindow(main_w, main_h, self.info_frame)
        self.preview_tmp_win = cw.CustomWindow(custom_w, custom_h)

        # Construct menus
        menubar = menu_bar.MenuBarWindow(self.preview_read_win, self.preview_tmp_win, self)

        # Define image_info layout
        self.image_info_layout = QVBoxLayout()
        self.image_info_layout.addWidget(self.preview_read_win)
        self.image_info_layout.addWidget(lines.get_h_line())
        self.image_info_layout.addWidget(sls.SlidersFrame(self.preview_read_win, self.preview_tmp_win))
        self.image_info_layout.addWidget(lines.get_h_line())
        self.image_info_layout.addWidget(self.info_frame)
        self.image_info_layout.setAlignment(Qt.AlignmentFlag.AlignTop)

        # Define image_info + vertical line layout
        image_info_line = QHBoxLayout()
        image_info_line.addLayout(self.image_info_layout)
        image_info_line.addWidget(lines.get_v_line())

        # Define image_info_frame
        image_info_frame = QFrame()
        image_info_frame.setLayout(image_info_line)
        image_info_frame.setFixedWidth(200)

        # Construct main windows
        self.main_layout = QHBoxLayout()
        self.main_layout.setMenuBar(menubar)
        self.main_layout.addWidget(image_info_frame)
        self.main_layout.addWidget(self.preview_tmp_win)

        # Construct main widget
        main_widget = QLabel()
        main_widget.setMinimumSize(900, 700)
        main_widget.setLayout(self.main_layout)
        main_widget.setSizePolicy(QSizePolicy.Policy.Expanding,
                                  QSizePolicy.Policy.Fixed)

        # Set Window parameters
        self.setWindowTitle("pyccante GUI [no image loaded]")
        self.setWindowIcon(QIcon("./data/icon.png"))

        # Set main windows
        self.setCentralWidget(main_widget)

    def update_window_title(self, text):
        self.setWindowTitle(f"pyccante GUI [{text}]")


if __name__ == '__main__':
    # Main function of the program
    # It creates the Qt Application and the main window

    # Create a Qt Application
    app = QApplication(sys.argv)

    # Create and show the form
    main_window = MainWindow()
    main_window.show()

    # Run the main Qt loop
    app.exec()

    # Deleting all the temp images
    print("Closing...")
    file.remove_temp_images()

    # Closing the program
    sys.exit()
