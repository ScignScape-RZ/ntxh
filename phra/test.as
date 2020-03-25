
void test_fn(PHRA_Binary_Channel@ pbc)
{
 PHRA_Runtime_Context@ prc = new_rt_context();
 prc.init_value_context(); 
 pbc.test_extract(1, 2);
}



void main()
{
 PHRA_Binary_Channel@ pbc = new_binary_channel();

 uint16 u = 1099;
 pbc.append(u);
//
 test_fn(pbc);

// lambda_88 l8(7);

//
 // print("Hello world\n");
// PHRA_Run_Context@ prc = init_gr();
// PHRA_Graph_Build@ pgb = prc.init_graph();
// pgb.test();
}


