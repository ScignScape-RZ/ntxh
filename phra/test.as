
void test_fn(PHRA_Binary_Channel@ pbc)
{
 PHRA_Runtime_Context@ prc = new_rt_context();
 PHRA_Value_Context@ pvc = prc.init_value_context();
 pvc.merge_binary_channel(pbc, 2, 5);

 PHRA_Channel_Package@ pcp = prc.new_channel_package();
 PHRA_Carrier_Channel@ pcc = pcp.add_carrier_channel("lambda");
 
 pcc.add_carrier("u2", "x", pvc.loc2(1088));

 pbc.test_extract(1, 2);
// uint16 u = pvc.get2v(5);
// print_u2(u);

}



void main()
{
 PHRA_Binary_Channel@ pbc = new_binary_channel();
 pbc.set_kind("lambda");

 uint16 u = 1099;
 pbc.append(u);

 uint32 uu = 101;
 pbc.append(uu);
 

//
 test_fn(pbc);

// lambda_88 l8(7);

//
 // print("Hello world\n");
// PHRA_Run_Context@ prc = init_gr();
// PHRA_Graph_Build@ pgb = prc.init_graph();
// pgb.test();
}


