// =============================================================================
//
// Copyright (c) 2014 Christopher Baker <http://christopherbaker.net>
// Copyright (c) -2014 Tom Carden <https://github.com/RandomEtc>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "AbstractMapProvider.h"
#include "MercatorProjection.h"


class OpenStreetMapProvider: public AbstractMapProvider
{
public:
    typedef std::shared_ptr<OpenStreetMapProvider> SharedPtr;

	OpenStreetMapProvider():
		AbstractMapProvider(AbstractProjection::SharedPtr(new MercatorProjection(0)))
	{
		_subdomains.push_back("");
		_subdomains.push_back("a.");
		_subdomains.push_back("b.");
		_subdomains.push_back("c.");
	}
	
	int getTileWidth() const
    {
		return 256;
	}
	
	int getTileHeight() const
    {
		return 256;
	}
	
    std::vector<std::string> getTileUrls(const Coordinate& rawCoordinate) const
    {
		std::vector<std::string> urls;

        if (rawCoordinate.row >= 0 && rawCoordinate.row < pow(2, rawCoordinate.zoom))
        {
			Coordinate coordinate = sourceCoordinate(rawCoordinate);

            std::stringstream url;

			std::string subdomain = _subdomains[(int)ofRandom(0, _subdomains.size())];

			url << "http://" << subdomain << "tile.openstreetmap.org/";
            url << (int)coordinate.zoom << "/" << (int)coordinate.column;
            url << "/" << (int)coordinate.row << ".png";

			urls.push_back(url.str());
		}
        
		return urls;
	}

    static SharedPtr makeShared()
    {
        return SharedPtr(new OpenStreetMapProvider());
    }

protected:
    std::vector<std::string> _subdomains;

	
};
