#ifndef _TEST_CARD_H_
#define _TEST_CARD_H_

namespace Library
{
namespace TestCard
{

void MakeColorBars(unsigned char* aImage, int aWidth, int aHeight);
void MakeSmpteColorBars(unsigned char* aImage, int aWidth, int aHeight);
void MakeSmpteColorBarsHD(unsigned char* aImage, int aWidth, int aHeight);

}
}

#endif
