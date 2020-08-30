int
width_tags(Bar *bar, BarWidthArg *a)
{
	int w, x = 0;
	unsigned int i, occ = 0, urg = 0;
	Client *c;
	Monitor *m = bar->mon;

	for (c = m->clients; c; c = c->next) {
		occ |= c->tags;
		if (c->isurgent)
			urg |= c->tags;
	}

	for (i = 0; i < LENGTH(tags); i++) {
		if (!(occ & 1 << i || m->tagset[m->seltags] & 1 << i))
			continue;
		w = TEXTW(tags[i]);
		x += w;
	}

	return x;
}

int
draw_tags(Bar *bar, BarDrawArg *a)
{
	int invert;
	int w, x = a->x;
	int boxs = drw->fonts->h / 9;
	int boxw = drw->fonts->h / 6 + 2;
	unsigned int i, occ = 0, urg = 0;
	Client *c;
	Monitor *m = bar->mon;

	for (c = m->clients; c; c = c->next) {
		occ |= c->tags;
		if (c->isurgent)
			urg |= c->tags;
	}

	for (i = 0; i < LENGTH(tags); i++) {
		if (!(occ & 1 << i || m->tagset[m->seltags] & 1 << i))
			continue;
		invert = urg & 1 << i;
		w = TEXTW(tags[i]);
		drw_setscheme(drw, scheme[m->tagset[m->seltags] & 1 << i ? SchemeSel : SchemeNorm]);
		drw_text(drw, x, 0, w, bh, lrpad / 2, tags[i], invert);
		if (occ & 1 << i)
			drw_rect(drw, x + boxs, boxs, boxw, boxw,
				m == selmon && selmon->sel && selmon->sel->tags & 1 << i, invert);
		x += w;
	}

	return x;
}

int
click_tags(Bar *bar, Arg *arg, BarClickArg *a)
{
	return -1;
}
