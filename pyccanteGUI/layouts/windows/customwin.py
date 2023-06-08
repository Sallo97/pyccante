# This files contains the derived class CustomImgWindow.


from layouts.windows import imgwindow as iw
from PySide6 import QtGui
from PySide6.QtCore import Qt
from PySide6.QtGui import QWheelEvent, QResizeEvent


class CustomImgWindow(iw.ImageWindow):
    # CustomImgWindow is a child of ImageWindow.
    # CustomImgWindow is the window to see the preview
    # image when all the action by the user are applyed.
    def __init__(self, win_width, win_height, info_layout=None):
        super().__init__(win_width, win_height, info_layout)

        # CustomImgWindow can change size depending on
        # the Pyccante GUI Window size at the moment.
        self.setMinimumSize(win_width, win_height)

        # mouse_flag is used to determine if the image
        # has been zoomed, if so when updating the
        # pixmap the size mustn't resize.
        self.mouse_flag = False

        # Set parameters to implement the zoom
        self.res_width = self.img.width
        self.res_height = self.img.height
        self.max_width = 4500
        self.max_height = 4500
        self.min_width = 10
        self.min_height = 10
        self.zoom = 1.5

        self.update_pixmap("")

    def resizeEvent(self, event: QResizeEvent):
        # When the Pyccante GUI has been resized,
        # We need to resize the pixmap too

        # Checks if the zoom has been applyed
        # and only when not we need to resize
        # the image
        if self.mouse_flag is False:
            self.update_pixmap("")

    def max_size_cond(self):
        # Returns True if the zoomed size
        # doesn't surpass the max limit,
        # return False otherwise.
        return self.res_width <= self.max_width or \
            self.res_height <= self.max_height

    def min_size_cond(self):
        # Returns True if the zoomed size
        # gets below the max limit,
        # return False otherwise.
        return self.res_width >= self.min_width or \
            self.res_height >= self.min_height

    def original_size(self, img=None):
        # Set the pixmap to show the image
        # at is original size.

        self.mouse_flag = False
        if img is not None:
            # If we are passing a new image
            # set the base zoom parameters to
            # the new image size
            self.res_width = img.width
            self.res_height = img.height
        else:
            # set the base zoom parameters to
            # the current image size
            self.res_width = self.img.width
            self.res_height = self.img.height
            self.update_pixmap("")

    def invert_w_h(self):
        # When rotating 90CW or 90CCW, when an image is zoomed,
        # we must update the res.width in res.height
        # and viceversa.
        # Not doing it will cause the image to
        # "get bigger" when rotating vertically.
        temp = self.res_width
        self.res_width = self.res_height
        self.res_height = temp

    def wheelEvent(self, event: QWheelEvent):
        # When the mouse wheel is moved inside
        # the CustomImageWindow, update the pixmap
        # enlarging or shrinking the image
        # and set mouse_flag to true
        # to keep the zoomed image consistent.
        if event.angleDelta().y() > 0:
            self.update_pixmap("+")
        else:
            self.update_pixmap("-")
        self.mouse_flag = True

    def update_pixmap(self, mouse="#"):
        # update_pixmap updates the pixmap of the image windows
        # mouse = checks if the mouse wheel has been moved and
        #         resize the image accordingly

        # Check if the mouse wheel has been moved
        if mouse == "+" and self.max_size_cond():
            self.res_width *= self.zoom
            self.res_height *= self.zoom
        elif mouse == "-" and self.min_size_cond():
            self.res_width /= self.zoom
            self.res_height /= self.zoom
        elif mouse != "#" and self.max_size_cond() and self.min_size_cond():
            self.res_width = self.img.width
            self.res_height = self.img.height
            # Resize the image to the windows size
            while self.res_width > self.width or self.res_height > self.height:
                self.res_width /= self.zoom
                self.res_height /= self.zoom

        # Load the image from raw data
        q_img = self.get_qimg()

        # Set a new pix_map
        new_pix_map = QtGui.QPixmap(q_img)
        new_pix_map = new_pix_map.scaled(self.res_width, self.res_height,
                                         Qt.AspectRatioMode.KeepAspectRatioByExpanding)
        self.setPixmap(new_pix_map)
        self.setAlignment(Qt.AlignCenter)

    def set_img(self, new_img):
        # Set the new image as the current one
        # new_img = the new image
        # resize = if True, resize the image to the windows size
        #          if False, keep the original size
        # Resize is necessary because when the user read a new image
        # or apply an algorithm, the new image must be displayed within
        # is dimensions and not the previous one.
        super().set_img(new_img)
        if new_img is not None:
            self.update_pixmap()

    def get_ldr(self):
        # Returns the current ldr_type
        return self.ldr_type

    def update_sliders(self, gamma=None, exp=None):
        # Update the exp and gamma values
        # when the apposite sliders are moved.
        # Set the new values and update the image
        # gamma = the new gamma value
        # exp = the new exp value.
        # It returns nothing.

        super().update_sliders(gamma, exp)

        if self.ext == "hdr":
            # We have to pass the mouse '#' value
            # to not reset the zoom
            self.update_pixmap("#")
