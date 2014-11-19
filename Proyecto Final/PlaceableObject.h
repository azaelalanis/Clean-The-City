/*
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* File for "Textures" lesson of the OpenGL tutorial on
 * www.videotutorialsrock.com
 */
/* Modified by Jesus De La Fuente Amaya on 10/25/2014
 *  All rights are reserved
 */

#pragma once
#include "addGlut.h"

class PlaceableObject
{
public:

	PlaceableObject()
	{
		setPositions(0, 0, 0);
		setSizes(1, 1, 1);
	}

	void setPositions(double x, double y, double z){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void setSizes(double height, double width, double volume){
		this->height = height;
		this->width = width;
		this->volume = volume;
	}

	virtual void draw() = 0;

protected:
	double x;
	double y;
	double z;
	double height;
	double width;
	double volume;
};

