
void test_fn(uint)
{
// PHRA_Runtime_Context@ prc = new_rt_context();
 PHRA_Binary_Channel@ pbc = new_binary_channel();
 uint64 u = 1234567891011;
 pbc.append(u);

// uint32 uu = 2025;
// pbc.append(uu);

// pbc.test_extract(1, 4);

// pbc.append(u);

// pbc.test_extract(13, 8);
 pbc.test_extract(1, 8);
// pbc.test_extract(9, 4);
 
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


