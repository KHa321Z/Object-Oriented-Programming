#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Image {

    private:

        char format[3];
        int maxGreyScale;
        int rows;
        int cols;
        unsigned short** image;

    public:

        Image() : format(), maxGreyScale(0), rows(0), cols(0), image(0) {}

        ~Image() {

            for (int i = 0; i < rows; i++)
                delete[] image[i];

            delete[] image;

        }

        /*Function for getting a single pixel at rth Row & cth Column*/
        int getPixel(int r, int c) {

            if (r >= this->rows || c >= this->cols || r < 0 || c < 0)
                return -1;

            return this->image[r][c];

        }

        unsigned short setPixel(unsigned short value, int r, int c) {

            if (r >= this->rows || c >= this->cols || r < 0 || c < 0)
                return -1;

            this->image[r][c] = value;
            return value;

        }

        int getRows() {
            return this->rows;
        }

        int setRows(int r) {

            if (r < 1)
                return -1;

            this->rows = r;
            return r;

        }

        int getCols() {
            return this->rows;
        }

        int setCols(int c) {

            if (c < 1)
                return -1;

            this->cols = c;
            return c;

        }

        bool saveImage(string File_Name) {

            /*
            * Here write the code to save an image in .pgm format
            * The function will return true if the image is saved successfully
            */

            fstream saveFile(File_Name + ".pgm", ios::out);

            if (saveFile.is_open()) {

                saveFile << this->format << endl;
                saveFile << this->cols << " " << this->rows << endl;
                saveFile << this->maxGreyScale << endl;

                for (int i = 0; i < this->rows; i++) {
                    for (int j = 0; j < this->cols; j++)
                        saveFile << this->image[i][j] << " ";

                    saveFile << endl;
                }

                saveFile.close();

                return true;

            }

            return false;

        }

        bool loadImage(string File_Name) {

            /*
            * Here write the code to load an image which is in .pgm format
            * into the struct member "Image"
            * The function will return true if the image is loaded successfully
            */
           
            fstream loadFile(File_Name + ".pgm", ios::in);

            if (loadFile.is_open()) {

                loadFile >> this->format;
                loadFile.ignore(70, '\n');
                
                if (loadFile.peek() == '#')
                    loadFile.ignore(70, '\n');
                
                loadFile >> this->cols >> this->rows;
                loadFile >> this->maxGreyScale;

                this->image = new unsigned short* [this->rows];

                for (int i = 0; i < this->rows; i++) {

                    this->image[i] = new unsigned short [this->cols];

                    for (int j = 0; j < this->cols; j++)
                        loadFile >> this->image[i][j];

                }

                loadFile.close();

                return true;

            }

            return false;

        }

        void Negative() {

            /*
            * Here write the code to convert the grayscale image into negative form
            * Tip: You need to blacken the pixels at every index
            */

            for (int i = 0; i < this->rows; i++)
                for (int j = 0; j < this->cols; j++)
                    this->image[i][j] = this->maxGreyScale - this->image[i][j];

        }


        void changeBrightness(double amount) {

            /*
            * Here write the code to brighten the grayscale image by the provided amount.
            * The range of amount is from -255 till +255
            * Tip: You need to brighten the pixels at every index
            */

            for (int i = 0; i < this->rows; i++)
                for (int j = 0; j < this->cols; j++)
                    this->image[i][j] = ((this->image[i][j] + amount) > this->maxGreyScale ? this->maxGreyScale : ((this->image[i][j] + amount) < 0 ? 0 : this->image[i][j] + amount));

        }

        void medianFilter(int filterSize = 3) {

            /*
            * Here write the code to apply the median filter on an image
            * This will reduce the noise in the image
            * Tip:
            * Here filtersize states the size of the matrix grid that will be created upon Image 2D Array i.e 3x3 by default
            * Find median of this array.
            * Then replace neighbouring pixels with the median value.
            * The following image can help you understand the concept: https://i.stack.imgur.com/P6Moj.png
            */

            for (int i = 1; i < this->rows - 1; i++) {

                for (int j = 1; j < this->cols - 1; j++) {

                    int index = 0;
                    int* median = new int [filterSize * filterSize];

                    for (int x = -filterSize / 2; x <= filterSize / 2; x++)
                        for (int y = -filterSize / 2; y <= filterSize / 2; y++)
                            median[index++] = this->image[i + x][j + y];

                    for (int i = 0; i < filterSize * filterSize - 1; i++)
                        for (int j = i; j < filterSize * filterSize - 1; j++)
                            if (median[j] > median[j + 1])
                                swap(median[j], median[j + 1]);

                    this->image[i][j] = median[filterSize * filterSize / 2];

                    delete[] median;

                }

            }

        }

        void combineSideBySide(Image& Two, int fillValue) {

            /*
            * Here write the code to combine the second image aside to the current image
            Tip: Adding two 2D arrays, increasing the resultant image size
            */

            int r = (this->rows > Two.rows) ? this->rows : Two.rows;
            unsigned short** tempImage = new unsigned short* [r];

            for (int i = 0; i < r; i++) {

                tempImage[i] = new unsigned short [this->cols + Two.cols];

                for (int j = 0; j < this->cols; j++)
                    tempImage[i][j] = (i < this->rows) ? this->image[i][j] : fillValue;

                for (int j = 0; j < Two.cols; j++)
                    tempImage[i][this->cols + j] = (i < Two.rows) ? Two.image[i][j] : fillValue;

                delete[] this->image[i];

            }

            delete this->image;

            this->rows = r;
            this->cols += Two.cols;
            this->image = tempImage;

        }

        void FlipHorizontally() {

            /*
            * Here write the code to flip the image horizontally
            Tip: swapping image pixels
            */

            for (int i = 0; i < this->rows; i++)
                for (int j = 0; j < this->cols / 2; j++)
                    swap(this->image[i][j], this->image[i][this->cols - j - 1]);

        }

        void FlipVertically() {

            /*
            * Here write the code to flip the image vertically
            Tip: swapping image pixels
            */

            for (int i = 0; i < this->rows / 2; i++)
                swap(this->image[i], this->image[this->rows - i - 1]);

        }

        /* BONUS TASK */
        void Filter(double Mask[][3], int ro, int co)
        {
            /*
            * Here write the code to apply a filter of user's choice on the image
            Tip: Use the mask array and enhance each pixel with index of 3x3 mask array
            */

            int l = 0, r = 0, z = 0, s = 0, x = 0, summ = 0;
            int n = ro / 2;

            cout << endl;
            cout << "Enter the Elements of Mask Filter Array " << endl;
            for (int q = 0; q < ro; q++)
            {
                for (int w = 0; w < co; w++)
                    cin >> Mask[q][w];
            }

        }

};

int main() {

	Image GM;
	string outputFile;
	string image1;

	cout << "Enter name of image 1: " << endl;
	getline(cin, image1);
	GM.loadImage(image1);

	int option = 0;

	while (option != -1)
	{
		cout << "Choose an option:\n" << endl;
		cout << " 1. Combine Two images side by side " << endl;
		cout << " 2. Change Brightness of Image" << endl;
		cout << " 3. Find Negative of an Image " << endl;
		cout << " 4. Flip an image Vertically" << endl;
		cout << " 5. Flip an image Horizontally" << endl;
		cout << " 6. Apply Median Filter (Remove Noise)" << endl;
		cout << " 7. Apply your own Filter (Bonus)" << endl;
		cout << "ENTER -1 TO EXIT" << endl;
		cin >> option;
		cout << endl;

		if (option == 1) //sidebyside
		{
			Image GM2;
			string image2;

			cout << "Enter name of image 2: " << endl;
            cin.ignore();
			getline(cin, image2);
			GM2.loadImage(image2);

			int fillVal;
			cout << "Enter the gray fill Value: " << endl;
			cin >> fillVal;
			GM.combineSideBySide(GM2, fillVal);
			cout << "Enter the output file name: ";
			cin >> outputFile;
			GM.saveImage(outputFile);
		}

		else if (option == 2) { //brightness
			int amount;
			cout << "Enter the amount for brightness: " << endl;
			cin >> amount;
			cout << endl;
			GM.changeBrightness(amount);
			cout << "Enter the output file name: ";
			cin >> outputFile;
			cout << endl;
			GM.saveImage(outputFile);
			cout << endl;
			cout << "Files Saved successfully in the output folder" << endl;
		}

		else if (option == 3) { //negative
			GM.Negative();
			cout << "Enter the output file name: ";
			cin >> outputFile;
			GM.saveImage(outputFile);
			cout << endl;
			cout << "Files Saved successfully in the output folder" << endl;
		}

		else if (option == 4) { //flip v
			GM.FlipVertically();
			cout << "Enter the output file name: ";
			cin >> outputFile;
			GM.saveImage(outputFile);
			cout << endl;
			cout << "Files Saved successfully in the output folder" << endl;
		}

		else if (option == 5) { //flip h
			GM.FlipHorizontally();
			cout << "Enter the output file name: ";
			cin >> outputFile;
			GM.saveImage(outputFile);
			cout << endl;
			cout << "Files Saved successfully in the output folder" << endl;
		}

		else if (option == 6) { //median

			int filtersize;
			cout << "Enter filter size: " << endl;
			cin >> filtersize;
			GM.medianFilter(filtersize);
			cout << "Enter the output file name: ";
			cin >> outputFile;
			cout << endl;
			GM.saveImage(outputFile);
			cout << endl;
			cout << "Files Saved successfully in the output folder" << endl;
		}

		else if (option == 7) { //Filter
			double b[3][3];
			int r = 3, c = 3;
			GM.Filter(b, r, c);
			cout << "Enter the output file name: ";
			cin >> outputFile;
			cout << endl;
			GM.saveImage(outputFile);
		}

		else if (option == -1)
			break;
	}

	return 0;

}