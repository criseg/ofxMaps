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


#pragma once


#include "AbstractProjection.h"
#include "Coordinate.h"
#include "Location.h"


class AbstractTileProvider
{
public:
    typedef std::shared_ptr<AbstractTileProvider> SharedPtr;

    AbstractTileProvider(AbstractProjection::SharedPtr projection):
        _projection(projection)
    {
    }
	
	virtual std::vector<std::string> getTileUrls(const Coordinate& coordinate) const = 0;

	virtual int getTileWidth() const = 0;
	virtual int getTileHeight() const = 0;
	
	Coordinate locationCoordinate(const Location& location) const
    {
		return _projection->locationCoordinate(location);
	}
	
	Location coordinateLocation(const Coordinate& coordinate) const
    {
		return _projection->coordinateLocation(coordinate);
	}
	
	Coordinate sourceCoordinate(const Coordinate& coordinate) const
    {
		double gridSize = pow(2.0, coordinate.zoom);
		
		double wrappedColumn = coordinate.column;
        
		if(wrappedColumn >= gridSize)
        {
			wrappedColumn = fmod(wrappedColumn, gridSize);
		}
		else
        {
			while (wrappedColumn < 0)
            {
				wrappedColumn += gridSize;
			}
		}
		
		return Coordinate(coordinate.row, wrappedColumn, coordinate.zoom);
	}

protected:
    AbstractProjection::SharedPtr _projection;
	
};
