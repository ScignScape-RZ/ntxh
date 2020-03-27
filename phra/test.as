
void test_fn(PHRA_Binary_Channel@ pbc)
{
 PHRA_Runtime_Context@ prc = new_rt_context();
 PHRA_Value_Context@ pvc = prc.init_value_context();
 pvc.merge_binary_channel(pbc, 2, pbc.short_mask());

 PHRA_Channel_Package@ pcp = prc.new_channel_package();
 pcp.add_fname("test_u2_u4");

 PHRA_Carrier_Channel@ pcc = pcp.add_carrier_channel("lambda");
 
 pcc.add_carrier("u2", "x", 5); // 5 = 1 << 2 | 1 ...
// pcc.add_carrier("u2", "x", pvc.loc2(1088));
// pcc.add_carrier("u4", "y", pvc.loc4(12));
 pcc.add_carrier("u4", "y", 6); // 6 = 1 << 2 | 2 ...

 PHRA_Binary_Channel@ pbc1 = pcc.to_binary(pvc);

 prc.run(pcp, pbc1);

 pbc1.test_extract(1, 2);
 pbc.test_extract(1, 2);

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


