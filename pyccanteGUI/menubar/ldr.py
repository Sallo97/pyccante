import pyccante as pyc
import imgwindow as iw


def none_action(img, path, win):
    img.Write(path, pyc.LDR_type.LT_NONE)
    win.update_pixmap(new_path=path)


def nor_action(img, path, win):
    img.Write(path, pyc.LDR_type.LT_NOR)
    win.update_pixmap(new_path=path)


def gam_action(img, path, win):
    img.Write(path, pyc.LDR_type.LT_NOR_GAMMA)
    win.update_pixmap(new_path=path)
