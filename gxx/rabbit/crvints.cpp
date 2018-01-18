#include <gxx/rabbit/intersect2.h>
#include <typeinfo>
#include <typeindex>
#include <map>

namespace rabbit {	
	using intsignature = 
		void(*)(
			const curve2&, const curve2&, 
			std::vector<double>&, std::vector<double>&, 
			const interval&, const interval&
		); 	

	void line_line_intersection(
		const curve2& acrv, const curve2& bcrv, 
		std::vector<double>& apnts, std::vector<double>& bpnts, 
		const interval& afltr, const interval& bfltr) 
	{
		const auto& a = static_cast<const gxx::geom2::line&>(acrv);
		const auto& b = static_cast<const gxx::geom2::line&>(bcrv);
	
		point l12 = a.l - b.l;
		double dd = a.d.crossmul(b.d);

		if (gxx::math::early_zero(dd, gxx::geom2::precision)) {
			//Прямые совпадают или паралельны.
			//Считаем, что пересечений нет.
			//Примечание: алгоритм ищет только пересечения.
			return;
		}
		
		//одна точка пересечения
		double t1 = b.d.crossmul(l12) / dd;
		double t2 = a.d.crossmul(l12) / dd;
		
		if (afltr.in_not_include(t1, gxx::geom2::precision) && bfltr.in_not_include(t2, gxx::geom2::precision)) {
			apnts.emplace_back(t1);
			bpnts.emplace_back(t2);
		}
		
		return;
	}

	std::map<std::pair<std::type_index, std::type_index>, intsignature> intsmap {
		{std::pair<std::type_index, std::type_index>(typeid(gxx::geom2::line), typeid(gxx::geom2::line)), line_line_intersection}, 
	};

	void curve_curve_intersection(
		const curve2& acrv, const curve2& bcrv, 
		std::vector<double>& apnts, std::vector<double>& bpnts, 
		const interval& afltr, const interval& bfltr) 
	{
		std::type_index atype = typeid(acrv); 
		std::type_index btype = typeid(bcrv);

		auto it = intsmap.find(std::pair<std::type_index, std::type_index>(atype, btype));
		if (it != intsmap.end()) {
			it->second(acrv, bcrv, apnts, bpnts, afltr, bfltr);
			return;
		} 

		it = intsmap.find(std::pair<std::type_index, std::type_index>(btype, atype));
		if (it != intsmap.end()) {
			it->second(bcrv, acrv, bpnts, apnts, bfltr, afltr);
			return;
		}
	}
}