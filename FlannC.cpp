#include "FlannC.h"

FlannC::FlannC()
{
	ponderation = 0;
	distance_max_x = 0;
	distance_max_y = 0;
}

FlannC::~FlannC()
{
}

float FlannC::getPonderation()
{
	return ponderation;
}

Point FlannC::getKeypoints_matched1(int i)
{
	return keypoints_matched1[i];
}

Point FlannC::getKeypoints_matched2(int i)
{
	return keypoints_matched2[i];
}

void FlannC::flannC_process( Mat img_1, Mat img_2 )
{
	if ( !img_1.data || !img_2.data )
	{
		std::cout << " --(!) Error reading images " << std::endl;
	}

	//-- Step 1: Detect the keypoints using SURF Detector
	int minHessian = 400;

	SurfFeatureDetector detector( minHessian );

	std::vector<KeyPoint> keypoints_1, keypoints_2;

	detector.detect( img_1, keypoints_1 );
	detector.detect( img_2, keypoints_2 );

	//-- Step 2: Calculate descriptors (feature vectors)
	SurfDescriptorExtractor extractor;

	Mat descriptors_1, descriptors_2;

	extractor.compute( img_1, keypoints_1, descriptors_1 );
	extractor.compute( img_2, keypoints_2, descriptors_2 );

	//-- Step 3: Matching descriptor vectors using FLANN matcher
	FlannBasedMatcher matcher;
	std::vector< DMatch > matches;
	matcher.match( descriptors_1, descriptors_2, matches );

	double max_dist = 0; double min_dist = 100;

	//-- Quick calculation of max and min distances between keypoints
	for ( int i = 0; i < descriptors_1.rows; i++ )
	{	double dist = matches[i].distance;
		if ( dist < min_dist ) min_dist = dist;
		if ( dist > max_dist ) max_dist = dist;
	}


	//-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist,
	//-- or a small arbitary value ( 0.02 ) in the event that min_dist is very
	//-- small)
	//-- PS.- radiusMatch can also be used here.
	std::vector< DMatch > good_matches;

	for ( int i = 0; i < descriptors_1.rows; i++ )
	{
		if ( matches[i].distance <= max(2 * min_dist, 0.02) )
		{
			good_matches.push_back( matches[i]);
		}
	}

	printf("-- Max dist : %f \n", max_dist );
	printf("-- Min dist : %f \n", min_dist );

	//-- Draw only "good" matches
	Mat img_matches;
	drawMatches( img_1, keypoints_1, img_2, keypoints_2,
	             good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
	             vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

	//-- Show detected matches
	imwrite("img/matches.jpg", img_matches );

	for (int i = 0; i < good_matches.size(); i++)
	{
		//On perd en précision car se sont des int et non plus des float
		Point kp1(keypoints_1[good_matches[i].queryIdx].pt.x, keypoints_1[good_matches[i].queryIdx].pt.y);
		Point kp2(keypoints_2[good_matches[i].trainIdx].pt.x, keypoints_2[good_matches[i].trainIdx].pt.y);
		keypoints_matched1.push_back(kp1);
		keypoints_matched2.push_back(kp2);

		printf("keypoint 1: x= %d  y= %d      keypoint 2: x=%d  y= %d\n", keypoints_matched1[i].x, keypoints_matched1[i].y, keypoints_matched2[i].x, keypoints_matched2[i].y);
	}

	// On récupère la distance entre les deux points les + distants (ou un truc comme ca)

	for ( int i = 0; i < (int)keypoints_matched2.size() - 1 ; i++ )
	{
		for (int j = i ; j < (int)keypoints_matched2.size() - 1 ; j++)
		{
//On prend la valeur absolue car on calcule des distances
			float distance_x = fabs(keypoints_matched2[i].x - keypoints_matched2[j].x);

			float distance_y = fabs(keypoints_matched2[i].y - keypoints_matched2[j].y);

			if (distance_max_x < distance_x)
			{
				distance_max_x = distance_x;
			}

			if (distance_max_y < distance_y)
			{
				distance_max_y = distance_y;
			}
		}
	}

	printf("DISTANCE:%d\n", distance_max_x + distance_max_y);

	// On cree une ponderation
	ponderation = distance_max_x + distance_max_y;

}
