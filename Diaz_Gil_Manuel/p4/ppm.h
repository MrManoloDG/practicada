// PPM simple library for Asedio game

#include "../simulador/Defense.h"

using namespace Asedio;

int WritePPM(const char *fileName, int width, int height, unsigned char *ptr ) 
{
    int x, y;
    unsigned char r, g, b;
    FILE *file = fopen(fileName, "wb");
    if (!file) {
        std::cerr << "Error opening file '" << fileName << "'" << std::endl;
        return -1;
    }

    fprintf(file, "P6\n# Image created by Asedio software (http://agsh.net)\n%d %d\n255\n", width, height);

    for (y = 0 ; y < height ; y++) {
        for (x = 0 ; x < width ; x++) {
            r = *(ptr+3*(y*width+x));  
            g = *(ptr+3*(y*width+x)+1);
            b = *(ptr+3*(y*width+x)+2);

            fprintf(file, "%c%c%c", r, g, b);
        }
    }
    
    fprintf(file, "\n");
    fclose(file);

    return 0;
}

unsigned char* dGetBaseMapImage(int nCellsHeight, int nCellsWidth, unsigned char gray1, unsigned char gray2) {
	unsigned char* pixels = new unsigned char[3 * nCellsWidth * nCellsHeight];

    unsigned char colors[2];
    colors[0] = gray1;
    colors[1] = gray2;

	int k = 0;
	for(int i = 0 ; i < nCellsHeight ; ++i) {
        int color = i % 2;
		for(int j = 0 ; j < nCellsWidth ; ++j) {
			pixels[k] = colors[color % 2]; ++k; // r
			pixels[k] = colors[color % 2]; ++k; // g
			pixels[k] = colors[color % 2]; ++k; // b
            ++color;
		}
	}

	return pixels;
}

unsigned char* dAddObstaclesToImage(unsigned char* pixels, bool** freeCells
                                    , int nCellsHeight, int nCellsWidth, unsigned char color) {
	int k = 0;
	for(int i = 0 ; i < nCellsHeight ; ++i) {
		for(int j = 0 ; j < nCellsWidth ; ++j) {
			if(!freeCells[i][j]) {
				pixels[k] = color; ++k; // r
				pixels[k] = color;; ++k; // g
				pixels[k] = color;; ++k; // b
			} else {
				k += 3;
			}
		}
	}

	return pixels;
}

unsigned char* dAddCellValuesToImage(unsigned char* pixels, float** cellsValue
                                    , int nCellsHeight, int nCellsWidth, unsigned char baseMapColor
                                    , bool invertedScale) {
	float min = INF_F;
	float max = 0;
    for(int i = 0 ; i < nCellsHeight ; ++i) {
        for(int j = 0 ; j < nCellsWidth ; ++j) {
            if(cellsValue[i][j] > 0 && cellsValue[i][j] < min) {
			    min = cellsValue[i][j];
		    }
		    if(cellsValue[i][j] > max) {
			    max = cellsValue[i][j];
		    }
        }
    }

	float invMax = 1.0f / (max-min);

	for(int i = 0 ; i < nCellsHeight ; ++i) {
        for(int j = 0 ; j < nCellsWidth ; ++j) {
		    if(cellsValue[i][j] >= min) {
                unsigned char color;
                if(invertedScale) {
                    color = (char)(baseMapColor * (1-((cellsValue[i][j] - min) * invMax)));
                } else {
			        color = (char)(baseMapColor * ((cellsValue[i][j] - min) * invMax));
                }

			    int pos = (i * nCellsWidth) + j;
			    pixels[pos * 3] = baseMapColor;
			    pixels[(pos * 3) + 1] = baseMapColor + color;
			    pixels[(pos * 3) + 2] = baseMapColor;
		    }
        }
    }	

	return pixels;
}

unsigned char* dAddPointToImage(unsigned char* pixels, int i, int j, int nCellsWidth
                                , unsigned char r, unsigned char g, unsigned char b) {

	int pos = (i * nCellsWidth) + j;
	pixels[pos * 3] = r;
	pixels[(pos * 3)+1] = g;
	pixels[(pos * 3)+2] = b;

	return pixels;
}

void dPrintMap(const char* filename, int nCellsHeight, int nCellsWidth
                         , float cellHeight, float cellWidth, bool** freeCells
                         , float** cellValues, std::list<Defense*> defenses, bool maxIsBetter) {
    
    unsigned char* pixels = dGetBaseMapImage(nCellsHeight, nCellsWidth, 127, 120);

    pixels = dAddObstaclesToImage(pixels, freeCells, nCellsHeight, nCellsWidth, 0);

    if(cellValues != NULL) {
        pixels = dAddCellValuesToImage(pixels, cellValues, nCellsHeight, nCellsWidth, 127, !maxIsBetter);
    }

    float invCellHeight = 1.0f / cellHeight;
    float invCellWidth = 1.0f / cellWidth;
    int i, j;
    for(std::list<Defense*>::iterator it = defenses.begin() ; it != defenses.end() ; ++it) {
        i = (int)((*it)->position.y * invCellHeight); 
        j = (int)((*it)->position.x * invCellWidth);
        pixels = dAddPointToImage(pixels, i, j, nCellsWidth, 255, 0, 0);
    }

    WritePPM(filename, nCellsWidth, nCellsHeight, pixels);
	delete[] pixels;
}