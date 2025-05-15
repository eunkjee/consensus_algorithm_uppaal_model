//This file was generated from (Academic) UPPAAL 4.1.24 (rev. 29A3ECA4E5FB0808), November 2019

/*

*/
E<> forall (i : s_id) NodeSlot(i).SlotSuccess

/*

*/
E<> forall (i : s_id) NodeSlot(i).SlotFail

/*

*/
E<> forall (i : s_id) NodeSlot(i).SlotUnknown

/*

*/
//NO_QUERY

/*

*/
//NO_QUERY

/*

*/
A[] forall (i : s_id) not NodeSlot(i).SlotFail

/*

*/
A[] forall (i : s_id) not NodeSlot(i).SlotUnknown

/*

*/
A[] forall (i : s_id) not (NodeSlot(i).SlotFail || NodeSlot(i).SlotUnknown)

/*

*/
//NO_QUERY
