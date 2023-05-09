import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { map, Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class DataService {
	constructor (private http: HttpClient){}
	items: any[]=[];
	
	//definir metodo SALVAR
	salvar(saludador:String[]){
		this.http.post<any>('https://tecweb-49256-default-rtdb.firebaseio.com//saludador.json', saludador)
		.subscribe(
			response => console.log ( 'respuesta '+response),
			error => console.log ( 'error '+error)
		);
	}
	mostrar():Observable<any[]>{
		return this.http.get('https://tecweb-49256-default-rtdb.firebaseio.com//saludador.json').pipe(
			map( (responseData: any) => {
				const items = [];
				for(const key in responseData){
					if (responseData.hasOwnProperty(key)){
						items.push({id:key, ...responseData[key] });
					}
				}
				return items;
			})
		)/*.subscribe(items => {console.log(items);});*/

	}


}
/* MÉTODO MOSTRAR 1: Muestra los datos de firebase en la consola
mostrar(){
	this.http.get('https://tecweb-49256-default-rtdb.firebaseio.com//saludador.json').pipe(
		map( (responseData: any) => {
			const items = [];
			for(const key in responseData){
				if (responseData.hasOwnProperty(key)){
					items.push({id:key, ...responseData[key] });
				}
			}
			return items;
		})
	).subscribe(items => {console.log(items);});

}
*/