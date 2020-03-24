
void test_fn(uint)
{
// PHRA_Runtime_Context@ prc = new_rt_context();
 PHRA_Binary_Channel@ pbc = new_binary_channel();
 uint16 u2 = 97;
 pbc.append(u2);

 pbc.append(7);
 pbc.append(u2);

 pbc.test_extract(5, 2);
 pbc.test_extract(1, 2);
 pbc.test_extract(3, 2);
 
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


