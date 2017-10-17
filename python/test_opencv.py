# MIT License

# Copyright (c) 2017 Tuxedo

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.


import os, sys
from pyseeta import Detector
from pyseeta import Aligner
from pyseeta import Identifier

try:
    import cv2
    import numpy as np
except ImportError:
    raise ImportError('opencv can not be found!')

def test_detector(model_path, img_name):
    print('test detector:')
    if model_path is None:
        print('test_detector: Please specify the path to the model folder')
        return;
    if img_name is None:
        print('test_detector: Please specify the path to the image file')
        return
    assert os.path.isdir(model_path) is True, 'test_detector: The model file path should be a folder'
    assert os.path.isfile(img_name) is True, 'test_detector: no such file'
    
    # load model
    model_path_fd = model_path + '/seeta_fd_frontal_v1.0.bin'
    detector = Detector(model_path_fd)
    detector.set_min_face_size(30)

    image_color = cv2.imread(img_name, cv2.IMREAD_COLOR)
    image_gray = cv2.cvtColor(image_color, cv2.COLOR_BGR2GRAY)
    faces = detector.detect(image_gray)

    for i, face in enumerate(faces):
        print('({0},{1},{2},{3}) score={4}'.format(face.left, face.top, face.right, face.bottom, face.score))
        cv2.rectangle(image_color, (face.left, face.top), (face.right, face.bottom), (0,255,0), thickness=2)
        cv2.putText(image_color, str(i), (face.left, face.bottom),cv2.FONT_HERSHEY_COMPLEX, 1, (0,255,0), thickness=1)
    cv2.imshow('test', image_color)
    cv2.waitKey(0)

    detector.release()

def test_aligner(model_path, img_name):
    print('test aligner:')

    if model_path is None:
        print('test_aligner: Please specify the path to the model folder')
        return;
    if img_name is None:
        print('test_aligner: Please specify the path to the image file')
        return
    assert os.path.isdir(model_path) is True, 'test_aligner: The model file path should be a folder'
    assert os.path.isfile(img_name) is True, 'test_aligner: no such file'
    
    # load model
    model_path_fd = model_path + '/seeta_fd_frontal_v1.0.bin'
    detector = Detector(model_path_fd)
    detector.set_min_face_size(30)
    model_path_fa = model_path + '/seeta_fa_v1.1.bin'
    aligner = Aligner(model_path_fa)

    image_color = cv2.imread(img_name, cv2.IMREAD_COLOR)
    image_gray = cv2.cvtColor(image_color, cv2.COLOR_BGR2GRAY)

    faces = detector.detect(image_gray)

    for face in faces:
        landmarks = aligner.align(image_gray, face)
        for point in landmarks:
            cv2.circle(image_color, point, 1, (0,255,0), 2)

    cv2.imshow('test aligner', image_color)
    cv2.waitKey(0)

    aligner.release()
    detector.release()

def test_identifier(model_path, img1_name, img2_name):
    print('test identifier:')
    if model_path is None:
        print('test_identifier: Please specify the path to the model folder')
        return;
    if img1_name is None:
        print('test_identifier: Please specify the path to the image file1')
        return
    if img2_name is None:
        print('test_identifier: Please specify the path to the image file2')
        return
    assert os.path.isdir(model_path) is True, 'test_identifier: The model file path should be a folder'
    assert os.path.isfile(img1_name) is True, 'test_identifier: no such image file1'
    assert os.path.isfile(img2_name) is True, 'test_identifier: no such image file2'
    
    # load model
    model_path_fd = model_path + '/seeta_fd_frontal_v1.0.bin'
    model_path_fa = model_path + '/seeta_fa_v1.1.bin'
    model_path_fr = model_path + '/seeta_fr_v1.0.bin'
    detector = Detector(model_path_fd)
    aligner = Aligner(model_path_fa)
    identifier = Identifier(model_path_fr)

    # load image
    image_color_A = cv2.imread(img1_name, cv2.IMREAD_COLOR)
    image_gray_A = cv2.cvtColor(image_color_A, cv2.COLOR_BGR2GRAY)
    image_color_B = cv2.imread(img2_name, cv2.IMREAD_COLOR)
    image_gray_B = cv2.cvtColor(image_color_B, cv2.COLOR_BGR2GRAY)
    # detect face in image
    faces_A = detector.detect(image_gray_A)
    faces_B = detector.detect(image_gray_B)

    if len(faces_A) and len(faces_B):
        landmarks_A = aligner.align(image_gray_A, faces_A[0])
        featA = identifier.extract_feature_with_crop(image_color_A, landmarks_A)
        cv2.rectangle(image_color_A, (faces_A[0].left, faces_A[0].top), (faces_A[0].right, faces_A[0].bottom), (0,255,0), thickness=2)
        sim_list = []
        for face in faces_B:
            landmarks_B = aligner.align(image_gray_B, face)
            featB = identifier.extract_feature_with_crop(image_color_B, landmarks_B)
            sim = identifier.calc_similarity(featA, featB)
            sim_list.append(sim)
        print('sim: {}'.format(sim_list))
        index = np.argmax(sim_list)
        for i, face in enumerate(faces_B):
            color = (0,255,0) if i == index else (0,0,255)
            cv2.rectangle(image_color_B, (face.left, face.top), (face.right, face.bottom), color, thickness=2)
    cv2.imshow('single', image_color_A)
    cv2.imshow('double', image_color_B)
    cv2.waitKey(0)

    identifier.release()
    aligner.release()
    detector.release()

if __name__ == '__main__':
    '''
    if len(sys.argv) != 4:
        print("execute this program by running:\n"
            "test_opencv.py ./model ./data/single.jpg ./data/double.jpg \n")
        exit()
    if len(sys.argv) == 4:
        model_path = sys.argv[1]
        img1_name = sys.argv[2]
        img2_name = sys.argv[3]
        test_detector(model_path, img1_name)
        test_aligner(model_path, img1_name)
        test_identifier(model_path, img1_name, img2_name)
    '''
    '''
    test_detector(model_path='./model', img_name = '../FaceDetection/data/0_1_1.jpg')
    test_aligner('./model', '../FaceAlignment/data/image_0001.png')
    test_identifier('./model', 
        '../FaceIdentification/data/test_face_recognizer/images/compare_im/Aaron_Peirsol_0001.jpg', 
        '../FaceIdentification/data/test_face_recognizer/images/compare_im/Aaron_Peirsol_0004.jpg')
    '''

    test_detector(model_path='./model', img_name = 'data/chloecalmon.png')
    test_aligner('./model', 'data/chloecalmon.png')
    test_identifier('./model', 'data/single.jpg', 'data/double.jpg')
