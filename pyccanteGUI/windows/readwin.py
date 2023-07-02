# This files contains the class ReadWindow derived from ImageWindow.

import utils.str_warning as sw
import windows.warningwin as ww
from windows import imgwindow as iw
from PySide6 import QtGui
from PySide6.QtGui import QResizeEvent
from PySide6.QtCore import Qt


class ReadWindow(iw.ImageWindow):
    # ReadWindow is a child of ImageWindow.
    # ReadWindow is the window to see the read
    # image without modification applied.
    def __init__(self, win_width, win_height, info_frame):
        super().__init__(win_width, win_height)

        # ImgWindow is fixed in the upper-left corner of the
        # Pyccante GUI and needs to stay the same size.
        self.setFixedSize(win_width, win_height)
        self.info_frame = info_frame
        self.info_frame.update_text(self.img)
        self.setAlignment(Qt.AlignCenter)

    def set_img(self, new_img):
        # Set a new image to the windows
        # new_img = the new image to set

        # Call the set_img method of ImgWindow
        super().set_img(new_img)

        # Update the pixmap with the new image
        self.update_pixmap()

    def update_pixmap(self):
        # Set a new pixmap for the window
        # using the new read image.

        # Get the QImg for the pixmap
        q_img = self.get_qimg()

        # Set the new pixmap for the window
        new_pix_map = QtGui.QPixmap(q_img)

        # For ImgWindow the pixmap must always scale the image inside the window.
        new_pix_map = new_pix_map.scaled(self.size(), Qt.AspectRatioMode.KeepAspectRatio)
        self.setPixmap(new_pix_map)
        self.setAlignment(Qt.AlignCenter)

    def resizeEvent(self, event: QResizeEvent):
        # When the Pyccante GUI has been resized,
        # We need to resize the pixmap too
        self.update_pixmap()

    def update_sliders(self, gamma=None, exp=None):
        # Update the exp and gamma values
        # when the apposite sliders are moved.
        # Set the new values and update the image
        # gamma = the new gamma value
        # exp = the new exp value.
        # It returns nothing.

        # Calls the ImgWindow super method
        super().update_sliders(gamma, exp)

        # Checks if the image is hdr before updating
        if self.ext == "hdr":
            self.update_pixmap()
        else:
            # If the image is LDR, launch a warning
            ww.WarningWindow(sw.ldr_slider_str()).exec()
