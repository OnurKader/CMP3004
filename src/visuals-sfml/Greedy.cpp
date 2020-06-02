#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <list>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

struct sehirler
{
	string sehirsayı;
	double x;
	double y;
};

// nodeların olusturduğu cizgiler arasını hesaplayıp, bunları compare ediyor
// bu sayede en kısayı bulup outputluyor
void uzakhesapla(list<sehirler>& yol, list<sehirler>& keys)
{
	double curry;
	double durant = 100000;
	list<sehirler>::iterator erP, erL;
	double x1, x2, y1, y2;

	erL = keys.begin();
	string minsehirsayı = erL->sehirsayı;
	erP = yol.begin();
	string edgen = erP->sehirsayı;

	// yollardaki cizgilerin arasını hesaplıyor
	for(erP = yol.begin(); erP != --yol.end(); ++erP)
	{
		for(erL = keys.begin(); erL != keys.end(); ++erL)
		{
			x1 = erP->x;
			y1 = erP->y;
			++erP;
			x2 = erP->x;
			y2 = erP->y;
			--erP;
			// anlık uzaklığı hesaplıyor
			curry = abs((x2 - x1) * (y1 - erL->y) - (x1 - erL->x) * (y2 - y1));
			curry /= sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

			// en kısayı replacelıyor daha lowersa
			if(curry < durant)
			{
				durant = curry;
				minsehirsayı = erL->sehirsayı;
				++erP;
				edgen = erP->sehirsayı;
				--erP;
			}
		}
	}

	erL = keys.begin();
	while(erL->sehirsayı != minsehirsayı)
	{
		++erL;
	}
	erP = yol.begin();
	while(erP->sehirsayı != edgen)
	{
		++erP;
	}
	yol.insert(erP, *erL);
	keys.erase(erL);
}

// 2 Şehrin structurenı alıyor
// aralarındaki farkı hesaplıyor
double dista(const sehirler& iz1, const sehirler& iz2)
{
	const double x = iz2.x - iz1.x;
	const double y = iz2.y - iz1.y;

	return sqrt(x * x + y * y);
}

// Sehirler listesini alıyor ve baslangıc node u //yol listesine ekliyor
// geçilen yollarıda siliyor
list<sehirler> yakinnode(list<sehirler>& keys)
{
	list<sehirler> yol;
	list<sehirler>::iterator er;
	double curry;
	double durant = 100000;
	string minsehirsayı = "0";

	yol.push_back(keys.front());

	// Start node ile baslangıc nodeun arasındaki farkı hesaplıyor ve en kısayı saveliyor
	for(er = ++keys.begin(); er != keys.end(); ++er)
	{
		curry = dista(yol.front(), *er);

		if(curry < durant)
		{
			durant = curry;
			minsehirsayı = er->sehirsayı;
		}
	}

	er = keys.begin();
	while(er->sehirsayı != minsehirsayı)
	{
		++er;
	}
	yol.push_back(*er);
	keys.erase(er);

	yol.push_back(sehirler());
	yol.back().sehirsayı = " ";
	yol.back().x = keys.front().x;
	yol.back().y = keys.front().y;
	keys.pop_front();

	return yol;
}

// txt dosyasını okuyor ve şehirlerin değerlerini listeye çekiyor
list<sehirler> koord(const char* fileName)
{
	ifstream input {fileName};
	list<sehirler> koordeger;
	string x, y;

	if(input)
	{
		for(size_t i = 0; i < 48; i++)
		{
			input >> x;
			input >> y;

			sehirler temp;
			temp.sehirsayı = to_string(i);
			temp.x = stod(x);
			temp.y = stod(y);
			koordeger.push_back(temp);
		}
	}

	return koordeger;
}

// listeyi okuyor ve listedeki elementleri ekrana yazıyor
void dlist(const list<sehirler>& L)
{
	for(const auto& elem: L)
		cout << elem.sehirsayı << " ";
}

#if 0
int main()
{
	// dosyadan okuduğu kısım listeye depoluyor
	list<sehirler> keyscity = koord("city.txt");
	list<sehirler>::iterator er;

	// en yakın node bulmak için
	list<sehirler> yolcity = yakinnode(keyscity);

	// en yakın edgleri bulma
	cout << "Yol: ";
	dlist(yolcity);
	cout << endl;

	const clock_t baslacity = clock();
	while(!keyscity.empty())
	{
		uzakhesapla(yolcity, keyscity);

		cout << "Yol: ";
		dlist(yolcity);
		cout << endl;
	}

	const clock_t soncity = clock();
	// zaman farkı
	const double durumcity = double(soncity - baslacity) / CLOCKS_PER_SEC;
	printf("Time: %lf\n", durumcity);

	// yollar arasındaki uzaklığı hesaplama
	double distance = 0.;
	sehirler next;
	for(er = yolcity.begin(); er != --yolcity.end(); ++er)
	{
		++er;
		next = *er;
		--er;

		distance += dista(*er, next);
	}

	printf("Distance: %lf\n", distance);

	return 0;
}
#endif

