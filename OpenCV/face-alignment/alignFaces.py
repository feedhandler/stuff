# USAGE
# python3 alignFaces.py --shape-predictor shape_predictor_68_face_landmarks.dat --image ~/Pictures/A_photo_a_day_2018/IMG_20180211_174645.jpg

# import the necessary packages
from imutils.face_utils import FaceAligner
from imutils.face_utils import rect_to_bb
import argparse
import imutils
import dlib
import cv2

from pathlib import Path

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()

ap.add_argument("-p", "--shape-predictor", required=True,
	help="path to facial landmark predictor")

ap.add_argument("-i", "--images", required=True,
	help="glob expression of image files e.g. 'pictures/*.jpg'")

args = vars(ap.parse_args())


import glob
imageFiles = glob.glob(args["images"])

if not imageFiles:
  print("Error: No files found")
  exit(1)

# ~ for imageFile in imageFiles:
  # ~ print(imageFile)




# initialize dlib's face detector (HOG-based) and then create
# the facial landmark predictor and the face aligner
detector = dlib.get_frontal_face_detector()
predictor = dlib.shape_predictor(args["shape_predictor"])
fa = FaceAligner(predictor, desiredFaceWidth=256)

for imageFile in imageFiles:
  print(imageFile)

  # load the input image, resize it, and convert it to grayscale
  image = cv2.imread(imageFile)
  image = imutils.resize(image, width=800)
  gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

  # show the original input image
  #cv2.imshow("Input", image)

  # detect faces in the grayscale image  
  rects = detector(gray, 2)

  # loop over the face detections - we're assuming only one face per image
  for rect in rects:
    # extract the ROI of the *original* face, then align the face
    # using facial landmarks
    (x, y, w, h) = rect_to_bb(rect)
    faceOrig = imutils.resize(image[y:y + h, x:x + w], width=256)
    faceAligned = fa.align(image, gray, rect)

    # ~ import uuid
    # ~ f = str(uuid.uuid4())
    # ~ cv2.imwrite("foo/" + f + ".png", faceAligned)

    cv2.imwrite("foo/" + Path(imageFile).stem + ".png", faceAligned)

    # display the output images
    # ~ cv2.imshow("Original", faceOrig)
    # ~ cv2.imshow("Aligned", faceAligned)
    # ~ cv2.waitKey(10000)
