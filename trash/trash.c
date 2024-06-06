	int j
	
	j = 0;
		while (j < 768)
		{
			if (j < r->lineO)
			{
				s->td.addr[j * s->td.line_length/4 + r] = s->map.f_color;
			}
			else if (j >= r->lineH + r->lineO)	
			{
				s->td.addr[j * s->td.line_length/4 + r] = s->map.c_color;
			}
			j++;
		}