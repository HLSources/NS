#ifndef AVH_ORDER_H
#define AVH_ORDER_H

#include "util/nowarnings.h"
#include "types.h"
#include "mod/AvHConstants.h"
#include "mod/AvHSpecials.h"

#ifdef AVH_CLIENT
#include "common/triangleapi.h"
#include "cl_dll/wrect.h"
#include "cl_dll/cl_dll.h"
#endif

#ifdef AVH_SERVER
#include "extdll.h"
class CBaseEntity;
#endif

const int kOrderStatusActive = 0;
const int kOrderStatusComplete = 1;
const int kOrderStatusCancelled = 2;

class AvHOrder
{
public:
	// Client
						#ifdef AVH_CLIENT
	int					ReceiveFromNetworkStream();
						#endif
						
	// Server			
						#ifdef AVH_SERVER
	int					SendToNetworkStream();
	bool				SetReceiver(const EntityInfo& entity);
	bool				Update();
	bool				operator==(const AvHOrder& inOrder) const;
	bool				operator!=(const AvHOrder& inOrder) const;
	void				operator=(const AvHOrder& inOrder);
						#endif
						
	// Shared			
						AvHOrder();
	void				ClearReceiver();
	bool				GetHasReceiver(int inPlayerIndex) const;
	EntityInfo			GetReceiver() const;
	int					GetTargetIndex() const;
	AvHOrderType		GetOrderType() const;
	AvHOrderTargetType	GetOrderTargetType() const;
	AvHUser3			GetTargetUser3Type() const;
	void				GetLocation(vec3_t& outPosition) const;
	void				GetOrderColor(float& outR, float& outG, float& outB, float& outA) const;

	bool				RemovePlayerFromReceivers(int inIndex);

	bool				GetOrderActive() const;
	bool				GetOrderCancelled() const;
	bool				GetOrderCompleted() const;
	void				SetOrderCompleted();

	void				SetTargetIndex(int inTargetIndex);
	void				SetOrderType(AvHOrderType inType);
	void				SetOrderTargetType(AvHOrderTargetType inTargetType);
	void				SetUser3TargetType(AvHUser3 inUser3);
	void				SetLocation(const vec3_t& inPosition);

	#ifdef AVH_SERVER
	int					GetOrderID() const;
	void				SetOrderID();

	float				GetTimeOrderCompleted() const;
	void				SetTimeOrderCompleted(float inTime);
	#endif
				
private:
	EntityInfo			mPlayer;
	AvHOrderType		mOrderType;
	AvHOrderTargetType	mOrderTargetType;
	AvHUser3			mOrderTargetUser3;
	vec3_t				mLocation;
	int					mTargetIndex;
	int					mOrderStatus;

	#ifdef AVH_SERVER
	float				mTimeOrderCompleted;
	int					mOrderID;
	#endif
};

typedef vector<AvHOrder> OrderListType;

void AvHChangeOrder(OrderListType& inList, const AvHOrder& inOrder);
//void AvHRemovePlayerFromOrders(OrderListType& inList, int inPlayerIndex);

// Must be shared
AvHOrderType AvHGetDefaultOrderType(AvHTeamNumber inTeam, const vec3_t& inOrigin, const vec3_t& inNormRay, int& outTargetIndex, vec3_t& outTargetPoint, AvHUser3& outUser3, AvHOrderTargetType& outTargetType);

#ifdef AVH_SERVER
bool AvHCreateSpecificOrder(AvHTeamNumber inTeam, const vec3_t& inOrigin, AvHOrderType inOrder, const vec3_t& inNormRay, AvHOrder& outOrder);
bool AvHToggleUseable(CBaseEntity* inUser, const vec3_t& inNormRay, const vec3_t& inPosition);
#endif

#endif