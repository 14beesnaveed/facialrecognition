# facial-recognition-opencv
Facial Recognition using OpenCV in C++

Project for OOP course (2015)

This project uses OpenCV library to detect, train and test human faces using fisherface algorithm. The UI was developed using MFC Applications in Visual Studio. Some notes on the project are copied below.


OpenCV is an open-source computer vision library. Open source means the original source code of the software is available which can be modified. Computer vision means acquiring, processing and extraction of data from digital images. OpenCV contains implementations of different functions for image processing.

This is a machine-learning based program. But we just used a built-in algorithm. We did not “learn” machine learning. We just learned about computer vision and how to use external libraries.

An Image is a 2-D matrix where each element is an array of [R,G,B] readings. 

In face recognition, we have to determine the pattern of these values which are specific to every person. We used fisherface algorithm.

.csv file: Comma separated values. We can save an excel sheet as a .csv file too instead of a .xlsx. We can open a .csv file with notepad and all the entries would appear row wise where each column is separated with commas.

Vectors: Simple arrays of any given data-type that do not have a limited memory allocation.

Procedure:

The project was divided in 3 modules:
Acquiring Raw Data
	
Took 5 photos from 10 people. The more photos we use for training, the better the accuracy. Also pictures taken from good quality cameras produce better results. 

 Processing the raw data and extracting required data

We had a separate software provided by our instructor. The software had a simple interface (see figure). We’d load all the training data and mark the eye coordinates with the cursor. When we’re done, we export the data in a .csv file. Let’s name it “eye.csv”.
Now, keep reading the images in a loop, storing them in matrices and extract the corresponding data from the eye.csv using a CSV file reader class. (Revise objects and classes in OOP). We use the coordinates of the right and left eye and measure the slope between the two. We use this angle to rotate the image. The purpose is to align the image if a person has tilted his face.
Detect the face of the person in the image and crop out all the background. (We have to specify what object do we want to detect or what kind of ‘pose’ of the face are we expecting. There are specific files for each kind of objects and we have to load that particular “classifier” in our program. 
Resize the image to a standard resolution say 200x200 pixels. All the pictures have to be the same resolution for compatibility with the OpenCV.
Overwrite the raw data. We now have a processed data-set all ready to be used in the training.


      

Using the data to train the computer using the algorithm
Create another .csv file that contains full file paths to the images followed by the label. A label is an integer value that we set for each person. The .csv will look something like this:



Now, open this .csv file programmatically and make two vectors. An integer type vector and a matrix type vector. We read this .csv file and parse its two columns. First column, which is the file path is used to read an image file which is then stored in a matrix. That matrix is “pushed” onto the 0th index of the matrix-type vector. The second column (the label) similarly goes into the integer-type vector. We now have the image in matrix form and its label at the 0th index of the corresponding vectors. We repeat this process for all the images of the data-set.

Now, when we have our complete data in the two vectors; we will use these to train our algorithm. Once, the training completes, we save our trained data in .yml format.

Using the software on a test image 

We first take a test image and detect if there’s any human face in it. If yes, we crop out the background and resize it again. Now the test image is comparable to the “kind of data-set” we trained our algorithm with. Now load the .yml file and simply predict the label. We simply create an integer variable for label and pass it into the predict function. The function after completion would change its value according the closest match with our data-set. Now, we simply add if and else statements to ‘give every label, the actual name of its owner’.



Main Functions Used:

String face_cascade = "haarcascade_frontalface_alt.xml"; (sum of white – sum of black) and compare to ideal black and white windows to detect an object.

namedWindow(window, 1); //Opens a window

Mat frame; //Makes a matrix object

face_cascade.detectMultiScale(greyScaleFrame, faces, 1.1, 3, 0, cv::Size(190, 190), cv::Size(200, 200)); //Detects Face



imwrite("F://cropped image.png", cropImg); //overwrite


double difference =  eye1_y - eye2_y ;      //Code to determine angle
		double denom = (eye1_x - eye2_x );
		double ratio = difference / denom;
		double angle_rad = atan(ratio);
		double angle = angle_rad*57.13;
rotate(frame, angle , rotated);



while (getline(file, line)) //Code to read CSV (just read it once)
	{
		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, label);
		if (!path.empty() && !label.empty()){
			images.push_back(imread(path, 0));
			labels.push_back(atoi(label.c_str()));
		}
	}




vector<Mat> images;
	vector<int> labels;
model->train(images, labels);

model->save("F:/Data Base/fisherface.yml");

model->predict(face_resized, label);

if (label == 0)
{ 
Pname = "Ali";
}                                    

if (label == 1)
{
Pname = "Asad";
}
