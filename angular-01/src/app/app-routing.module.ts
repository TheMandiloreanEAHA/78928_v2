import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterModule, Routes } from '@angular/router';
import { InicioComponent } from './inicio/inicio.component';
import { AcercaComponent } from './acerca/acerca.component';
import { ContactoComponent } from './contacto/contacto.component';

const routes: Routes = [
  {path:'inicio',component: InicioComponent},
  {path:'acerca',component: AcercaComponent},
  {path:'contacto',component: ContactoComponent},
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
