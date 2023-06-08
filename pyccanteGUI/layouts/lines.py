# This file contains multiple functions that return a QFrame containing a line.
# These lines are used to separate different sections of the GUI.

from PySide6.QtWidgets import QFrame, QSizePolicy


def get_h_line(frame=None):
    # Returns a QFrame containing a horizontal line
    # It is used to separate different sections of the GUI
    if frame is None:
        frame = QFrame()
    frame.setFrameShape(QFrame.Shape.HLine)
    frame.setFrameShadow(QFrame.Shadow.Sunken)
    return frame


def get_v_line():
    # Returns a QFrame containing a vertical line
    # It is used to separate different sections of the GUI
    v_sep = QFrame()
    v_sep.setFrameShape(QFrame.Shape.VLine)
    v_sep.setFrameShadow(QFrame.Shadow.Sunken)
    v_sep.setSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Expanding)
    return v_sep
