
void test_fn(uint)
{
// PHRA_Runtime_Context@ prc = new_rt_context();
 PHRA_Binary_Channel@ pbc = new_binary_channel();
// uint16 u = 1097;
// pbc.append(u);

 uint32 uu = 2025;
 pbc.append(uu);

 pbc.test_extract(1, 4);

// pbc.append(u);

// pbc.test_extract(7, 2);
// pbc.test_extract(1, 2);
// pbc.test_extract(3, 4);
 
}



void main()
{
//
 test_fn(99);

// lambda_88 l8(7);

//
 // print("Hello world\n");
// PHRA_Run_Context@ prc = init_gr();
// PHRA_Graph_Build@ pgb = prc.init_graph();
// pgb.test();
}


