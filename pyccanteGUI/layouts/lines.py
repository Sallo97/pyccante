# This file contains multiple functions that return a QFrame containing a line.
# These lines are used to separate different sections of the GUI.

from PySide6.QtWidgets import QFrame, QSizePolicy, QVBoxLayout


class HLineFrame(QFrame):
    def __init__(self, frame=None):
        super(HLineFrame, self).__init__()
        self.setFrameShape(QFrame.Shape.HLine)
        self.setFrameShadow(QFrame.Shadow.Sunken)
        self.setSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Expanding)
        self.h_layout = QVBoxLayout()
        self.h_layout.addWidget(self)

def get_h_line(frame=None):
    # Returns a Qframe containing a horizontal line
    # It is used to separate different sections of the GUI
    if frame is None:
        frame = QFrame()
    frame.setFrameShape(QFrame.Shape.HLine)
    frame.setFrameShadow(QFrame.Shadow.Sunken)
    return frame


def get_v_line():
    # Returns a Qframe containing a vertical line
    # It is used to separate different sections of the GUI
    v_sep = QFrame()
    v_sep.setFrameShape(QFrame.Shape.VLine)
    v_sep.setFrameShadow(QFrame.Shadow.Sunken)
    v_sep.setSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Expanding)
    return v_sep
