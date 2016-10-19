//Given an interval list which are flying and landing time of the flight. 
//How many airplanes are on the sky at most?

/*
	* Definition of Interval:
	* classs Interval {
	*     int start, end;
	*     Interval(int start, int end) {
	*         this->start = start;
	*         this->end = end;
	*     }
	*/

class Solution {
	public:
		/**
			*      * @param intervals: An interval array
			*           * @return: Count of airplanes are in the sky.
			*                */
		int countOfAirplanes(vector<Interval> &airplanes) {
			int rst = 0;
			int count = 0;
			vector<pair<int, char>> points; 
			for (auto item : airplanes) {
				points.emplace_back(item.start, 's');
				points.emplace_back(item.end, 'e');
			}
			sort(points.begin(), points.end());
			for (auto p : points) {
				if (p.second == 's') {
					count++;
				} else {
					count--;
				}
				rst = max(rst, count);
			} 
			return rst;
		}
};
