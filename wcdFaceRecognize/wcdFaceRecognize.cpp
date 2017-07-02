#include"wcdFaceRecognize.h"

FR_FaceDetectCallBack g_pFaceDetectFunc = NULL;
FR_FaceVerifyCallBack g_pFaceVerifyFunc = NULL;

static const int Table_fv1[256] = { -180, -179, -177, -176, -174, -173, -172, -170, -169, -167, -166, -165, -163, -162, -160, -159, -158, -156, -155, -153, -152, -151, -149, -148, -146, -145, -144, -142, -141, -139, -138, -137, -135, -134, -132, -131, -130, -128, -127, -125, -124, -123, -121, -120, -118, -117, -115, -114, -113, -111, -110, -108, -107, -106, -104, -103, -101, -100, -99, -97, -96, -94, -93, -92, -90, -89, -87, -86, -85, -83, -82, -80, -79, -78, -76, -75, -73, -72, -71, -69, -68, -66, -65, -64, -62, -61, -59, -58, -57, -55, -54, -52, -51, -50, -48, -47, -45, -44, -43, -41, -40, -38, -37, -36, -34, -33, -31, -30, -29, -27, -26, -24, -23, -22, -20, -19, -17, -16, -15, -13, -12, -10, -9, -8, -6, -5, -3, -2, 0, 1, 2, 4, 5, 7, 8, 9, 11, 12, 14, 15, 16, 18, 19, 21, 22, 23, 25, 26, 28, 29, 30, 32, 33, 35, 36, 37, 39, 40, 42, 43, 44, 46, 47, 49, 50, 51, 53, 54, 56, 57, 58, 60, 61, 63, 64, 65, 67, 68, 70, 71, 72, 74, 75, 77, 78, 79, 81, 82, 84, 85, 86, 88, 89, 91, 92, 93, 95, 96, 98, 99, 100, 102, 103, 105, 106, 107, 109, 110, 112, 113, 114, 116, 117, 119, 120, 122, 123, 124, 126, 127, 129, 130, 131, 133, 134, 136, 137, 138, 140, 141, 143, 144, 145, 147, 148, 150, 151, 152, 154, 155, 157, 158, 159, 161, 162, 164, 165, 166, 168, 169, 171, 172, 173, 175, 176, 178 };
static const int Table_fv2[256] = { -92, -91, -91, -90, -89, -88, -88, -87, -86, -86, -85, -84, -83, -83, -82, -81, -81, -80, -79, -78, -78, -77, -76, -76, -75, -74, -73, -73, -72, -71, -71, -70, -69, -68, -68, -67, -66, -66, -65, -64, -63, -63, -62, -61, -61, -60, -59, -58, -58, -57, -56, -56, -55, -54, -53, -53, -52, -51, -51, -50, -49, -48, -48, -47, -46, -46, -45, -44, -43, -43, -42, -41, -41, -40, -39, -38, -38, -37, -36, -36, -35, -34, -33, -33, -32, -31, -31, -30, -29, -28, -28, -27, -26, -26, -25, -24, -23, -23, -22, -21, -21, -20, -19, -18, -18, -17, -16, -16, -15, -14, -13, -13, -12, -11, -11, -10, -9, -8, -8, -7, -6, -6, -5, -4, -3, -3, -2, -1, 0, 0, 1, 2, 2, 3, 4, 5, 5, 6, 7, 7, 8, 9, 10, 10, 11, 12, 12, 13, 14, 15, 15, 16, 17, 17, 18, 19, 20, 20, 21, 22, 22, 23, 24, 25, 25, 26, 27, 27, 28, 29, 30, 30, 31, 32, 32, 33, 34, 35, 35, 36, 37, 37, 38, 39, 40, 40, 41, 42, 42, 43, 44, 45, 45, 46, 47, 47, 48, 49, 50, 50, 51, 52, 52, 53, 54, 55, 55, 56, 57, 57, 58, 59, 60, 60, 61, 62, 62, 63, 64, 65, 65, 66, 67, 67, 68, 69, 70, 70, 71, 72, 72, 73, 74, 75, 75, 76, 77, 77, 78, 79, 80, 80, 81, 82, 82, 83, 84, 85, 85, 86, 87, 87, 88, 89, 90, 90 };
static const int Table_fu1[256] = { -44, -44, -44, -43, -43, -43, -42, -42, -42, -41, -41, -41, -40, -40, -40, -39, -39, -39, -38, -38, -38, -37, -37, -37, -36, -36, -36, -35, -35, -35, -34, -34, -33, -33, -33, -32, -32, -32, -31, -31, -31, -30, -30, -30, -29, -29, -29, -28, -28, -28, -27, -27, -27, -26, -26, -26, -25, -25, -25, -24, -24, -24, -23, -23, -22, -22, -22, -21, -21, -21, -20, -20, -20, -19, -19, -19, -18, -18, -18, -17, -17, -17, -16, -16, -16, -15, -15, -15, -14, -14, -14, -13, -13, -13, -12, -12, -11, -11, -11, -10, -10, -10, -9, -9, -9, -8, -8, -8, -7, -7, -7, -6, -6, -6, -5, -5, -5, -4, -4, -4, -3, -3, -3, -2, -2, -2, -1, -1, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15, 15, 16, 16, 16, 17, 17, 17, 18, 18, 18, 19, 19, 19, 20, 20, 20, 21, 21, 22, 22, 22, 23, 23, 23, 24, 24, 24, 25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28, 29, 29, 29, 30, 30, 30, 31, 31, 31, 32, 32, 33, 33, 33, 34, 34, 34, 35, 35, 35, 36, 36, 36, 37, 37, 37, 38, 38, 38, 39, 39, 39, 40, 40, 40, 41, 41, 41, 42, 42, 42, 43, 43 };
static const int Table_fu2[256] = { -227, -226, -224, -222, -220, -219, -217, -215, -213, -212, -210, -208, -206, -204, -203, -201, -199, -197, -196, -194, -192, -190, -188, -187, -185, -183, -181, -180, -178, -176, -174, -173, -171, -169, -167, -165, -164, -162, -160, -158, -157, -155, -153, -151, -149, -148, -146, -144, -142, -141, -139, -137, -135, -134, -132, -130, -128, -126, -125, -123, -121, -119, -118, -116, -114, -112, -110, -109, -107, -105, -103, -102, -100, -98, -96, -94, -93, -91, -89, -87, -86, -84, -82, -80, -79, -77, -75, -73, -71, -70, -68, -66, -64, -63, -61, -59, -57, -55, -54, -52, -50, -48, -47, -45, -43, -41, -40, -38, -36, -34, -32, -31, -29, -27, -25, -24, -22, -20, -18, -16, -15, -13, -11, -9, -8, -6, -4, -2, 0, 1, 3, 5, 7, 8, 10, 12, 14, 15, 17, 19, 21, 23, 24, 26, 28, 30, 31, 33, 35, 37, 39, 40, 42, 44, 46, 47, 49, 51, 53, 54, 56, 58, 60, 62, 63, 65, 67, 69, 70, 72, 74, 76, 78, 79, 81, 83, 85, 86, 88, 90, 92, 93, 95, 97, 99, 101, 102, 104, 106, 108, 109, 111, 113, 115, 117, 118, 120, 122, 124, 125, 127, 129, 131, 133, 134, 136, 138, 140, 141, 143, 145, 147, 148, 150, 152, 154, 156, 157, 159, 161, 163, 164, 166, 168, 170, 172, 173, 175, 177, 179, 180, 182, 184, 186, 187, 189, 191, 193, 195, 196, 198, 200, 202, 203, 205, 207, 209, 211, 212, 214, 216, 218, 219, 221, 223, 225 };


bool YV12toBGR(unsigned char *pYV12, unsigned char *pBGR24, int width, int height)
{
	if (!pYV12 || !pBGR24)
		return false;

	long int ylen = width * height;
	int hfwidth = width >> 1;

	unsigned char *pY = pYV12;
	unsigned char *pV = &pYV12[ylen];
	unsigned char *pU = &pYV12[(ylen * 5) >> 2];

	int bgr[3];
	int i, j, m, n, x, y, pu, pv, py, rdif, invgdif, bdif;
	m = -width;
	n = -hfwidth;
	bool addhalf = true;
	for (y = 0; y<height; y++) {
		m += width;
		if (addhalf){
			n += hfwidth;
			addhalf = false;
		}
		else {
			addhalf = true;
		}
		for (x = 0; x<width; x++) {
			i = m + x;
			j = n + (x >> 1);

			py = (unsigned char)pY[i];
			pv = (unsigned char)pV[j];
			pu = (unsigned char)pU[j];
			rdif = Table_fv1[pv];						// fv1
			invgdif = Table_fu1[pu] + Table_fv2[pv];	// fu1+fv2
			bdif = Table_fu2[pu];						// fu2
			bgr[2] = py + rdif;			// R
			bgr[1] = py - invgdif;		// G
			bgr[0] = py + bdif;			// B

			j = m + x;
			i = (j << 1) + j;

			// copy this pixel to bgr data
			for (j = 0; j<3; j++)
			{
				if (bgr[j] >= 0 && bgr[j] <= 255){
					pBGR24[i + j] = (unsigned char)bgr[j];
				}
				else{
					pBGR24[i + j] = (bgr[j] < 0) ? 0 : 255;
				}
			}
		}
	}
	return true;
}

//DLL初始化
bool __stdcall FR_Init(FR_FaceDetectCallBack FFCB, FR_FaceVerifyCallBack MFCB)
{
	g_pFaceDetectFunc = FFCB;
	g_pFaceVerifyFunc = MFCB;
	return true;
}

//DLL反初始化
bool __stdcall FR_Final()
{
	g_pFaceDetectFunc = NULL;
	g_pFaceVerifyFunc = NULL;
	return true;
}

int __stdcall FR_AddVerifyTarget(char* VTGUID, BYTE* VTPhoto, int VTPhotoLen)
{
	Mat bufImage(1, VTPhotoLen, CV_8UC1);
	memcpy(bufImage.data, VTPhoto, VTPhotoLen);
	Mat MImageBGR = imdecode(bufImage, CV_LOAD_IMAGE_COLOR);//BMP解码

	Mat detect_face = FaceDetect_(MImageBGR);
	vector<float> feature = ExtractFeature_(detect_face);

	string name(VTGUID);
	Mat saveFeature = Vector2dToMat(feature);
	SaveName(name, "..//data//Name.txt");
	SaveMat(saveFeature, string("..//data//") + name + ".xml");
	return true;
}

int __stdcall FR_DelVerifyTarget(char* VTGUID)
{
	string name(VTGUID);
	ifstream in("..//data//Name.txt");
	string s;
	vector<string> name_;
	while (getline(in, s))
		name_.push_back(s);
	for (auto it = name_.begin(); it != name_.end(); ++it)
	{
		if (*it == name)
			name_.erase(it);
	}
	in.close();

	ofstream out("..//data//Name.txt");
	for (int i = 0; i < name_.size(); i++)
		out << name_[i] << endl;

	remove((string("..//data//") + name + ".xml").c_str());
	return true;

}

int __stdcall FR_ClearVerifyTarget()
{
	return false;
}

//人脸检测：系统取得图像后调用FaceDetect输入RGB数据，FaceDetect分析发现人脸后返回人脸的数量。每发现一个人脸调用FaceDetectCallBack输出一次人脸数据。
int __stdcall FR_FaceDetect(BYTE* AFrame, int PhotoLen, int UserData, int flag)
{
	Mat bufImage(1, PhotoLen, CV_8UC1, AFrame);
	Mat MImageBGR = imdecode(bufImage, CV_LOAD_IMAGE_COLOR);//BMP解码

	if (flag == SHOW_IMAGE)
	{
		Mat MTest = Mat::zeros(100, 100, CV_8UC1);
		imshow("FaceDetect_MImageBGR", MImageBGR);
		imshow("MTest", MTest);
		waitKey(20);
	}

	Rect face_rect = FaceDetect_(MImageBGR, 0);
	vector<uchar> detect_face;
	imencode(".bmp", MImageBGR(face_rect), detect_face);
	int length = (int)detect_face.size();
	char* guid = "guid";
	if (g_pFaceDetectFunc)
	{
		(*g_pFaceDetectFunc)(guid, &detect_face[0], length*sizeof(uchar), face_rect.x, face_rect.y, face_rect.width, face_rect.height, UserData);
	}
	return true;


}

int __stdcall FR_FaceDetectSingle(BYTE* AFrame, int PhotoLen, BYTE* &AFace, int &FaceLen)
{
	return true;
}

int __stdcall FR_FaceVerify(BYTE* FaceAPhoto, int FaceAPhotoLen, BYTE* FaceBPhoto, int FaceBPhotoLen)
{
	Mat bufImageA(1, FaceAPhotoLen, CV_8UC1);
	memcpy(bufImageA.data, FaceAPhoto, FaceAPhotoLen);
	Mat MImageBGR_A = imdecode(bufImageA, CV_LOAD_IMAGE_COLOR);//BMP解码

	Mat bufImageB(1, FaceBPhotoLen, CV_8UC1);
	memcpy(bufImageB.data, FaceBPhoto, FaceBPhotoLen);
	Mat MImageBGR_B = imdecode(bufImageB, CV_LOAD_IMAGE_COLOR);//BMP解码

	Mat detect_faceA = FaceDetect_(MImageBGR_A);
	Mat detect_faceB = FaceDetect_(MImageBGR_B);
	vector<float> featureA = ExtractFeature_(detect_faceA);
	vector<float> featureB = ExtractFeature_(detect_faceA);
	int rate = 100 * (int)cosine(featureA, featureB);
	return rate;
}

int __stdcall FR_FaceListVerify(BYTE* FacePhoto, int FacePhotoLen, char* VTGUID, int UserData)
{
	Mat bufImage(1, FacePhotoLen, CV_8UC1);
	memcpy(bufImage.data, FacePhoto, FacePhotoLen);
	Mat MImageBGR = imdecode(bufImage, CV_LOAD_IMAGE_COLOR);//BMP解码

	Mat detect_face = FaceDetect_(MImageBGR);


}

bool __stdcall FR_Test()
{
	return true;
}

vector<float> __stdcall ExtractFeature_(Mat iptImage)
{
	return ExtractFeature(iptImage);
}

Mat FaceDetect_(Mat iptImage)
{
	Mat gray;
	cvtColor(iptImage, gray, CV_BGR2GRAY);

	int doLandmark = 1;
	int * pResults = NULL;
	unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
	pResults = facedetect_multiview_reinforce(pBuffer, (unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, (int)gray.step,
		1.2f, 3, 48, 0, doLandmark);
	//dlib.
	//
	int p_num = (pResults ? *pResults : 0);


	short * p = ((short*)(pResults + 1));
	Point left(p[0], p[1]);
	Point right(p[0] + p[2], p[1] + p[3]);
	Rect rect = Rect(left, right);
	Mat mat;
	mat = iptImage(rect);
	resize(mat, mat, Size(224, 224));
	return mat;
}

Rect FaceDetect_(Mat iptImage, int flag)
{
	Mat gray;
	cvtColor(iptImage, gray, CV_BGR2GRAY);

	int doLandmark = 1;
	int * pResults = NULL;
	unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
	pResults = facedetect_multiview_reinforce(pBuffer, (unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, (int)gray.step,
		1.2f, 3, 48, 0, doLandmark);

	int p_num = (pResults ? *pResults : 0);


	short * p = ((short*)(pResults + 1));
	Point left(p[0], p[1]);
	Point right(p[0] + p[2], p[1] + p[3]);
	Rect rect = Rect(left, right);
	return rect;
}

Mat Vector2dToMat(vector<float> feature)
{
	Mat T(1, 2622, CV_32F);

	for (int i; i < feature.size(); i++)
	{
		T.at<float>(0, i) = feature[i];
	}

	return T;
}

void SaveMat(Mat &saveFeature, const string& filename)
{
	FileStorage fs(filename, FileStorage::WRITE);
	fs << "FaceMatrix" << saveFeature;
	fs.release();
}

void SaveName(const string& name, const string& filename)
{
	ofstream out_(filename, ofstream::app);
	out_ << name << endl;
}

float dotProduct(const vector<float>& v1, const vector<float>& v2)
{
	assert(v1.size() == v2.size());
	float ret = 0.0;
	for (vector<float>::size_type i = 0; i != v1.size(); ++i)
	{
		if (v1[i] > 1000 || v2[i] > 1000 || v1[i] < (-1000) || v2[i] < (-1000))
			continue;
		else if (!(isnan(v1[i]) || isnan(v2[i])))
			ret += v1[i] * v2[i];
	}
	return ret;
}
float module(const vector<float>& v)
{
	float ret = 0.0;
	for (vector<float>::size_type i = 0; i != v.size(); ++i)
	{
		if (v[i] > 1000 || v[i]<(-1000))
			continue;
		else if (!isnan(v[i]))
			ret += v[i] * v[i];
	}
	return sqrt(ret);
}
float cosine(const vector<float>& v1, const vector<float>& v2)
{
	assert(v1.size() == v2.size());
	float f = 0.0;
	//cout << module(v1) << " " << module(v2) << endl;
	if ((module(v1) * module(v2)) == 0)
		f = 0;
	else
		f = dotProduct(v1, v2) / (module(v1) * module(v2));
	return f;
}