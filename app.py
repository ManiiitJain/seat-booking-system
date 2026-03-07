import os
from flask import Flask, render_template, request, jsonify
from supabase import create_client, Client
from dotenv import load_dotenv

# Load local environment variables if a .env file is present
load_dotenv()

app = Flask(__name__)

SUPABASE_URL = os.getenv("SUPABASE_URL")
SUPABASE_KEY = os.getenv("SUPABASE_KEY")

supabase: Client = None
if SUPABASE_URL and SUPABASE_KEY:
    supabase = create_client(SUPABASE_URL, SUPABASE_KEY)
else:
    print("WARNING: SUPABASE_URL or SUPABASE_KEY is missing from environment variables.")

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/api/seats', methods=['GET'])
def get_seats():
    if not supabase:
        return jsonify([])
    try:
        response = supabase.table('seats').select('*').order('id').execute()
        return jsonify(response.data)
    except Exception as e:
        return jsonify({"success": False, "message": str(e)}), 500

@app.route('/api/book', methods=['POST'])
def book_seat():
    if not supabase:
        return jsonify({"success": False, "message": "Database disconnected"}), 500
        
    data = request.json
    seat_id = data.get('id')
    name = data.get('name')
    gender = data.get('gender')
    
    if not seat_id or not name or not gender:
        return jsonify({"success": False, "message": "Missing fields"}), 400

    try:
        seat_res = supabase.table('seats').select('*').eq('id', int(seat_id)).execute()
        if not seat_res.data:
            return jsonify({"success": False, "message": "Seat not found"}), 404
            
        seat = seat_res.data[0]
        if seat['status'] == "Booked":
            return jsonify({"success": False, "message": "Seat already booked"}), 400
            
        supabase.table('seats').update({
            'status': 'Booked',
            'name': name,
            'gender': gender
        }).eq('id', int(seat_id)).execute()
        
        return jsonify({"success": True, "message": f"Seat {seat_id} booked successfully!"})
    except Exception as e:
        return jsonify({"success": False, "message": str(e)}), 500

@app.route('/api/cancel', methods=['POST'])
def cancel_seat():
    if not supabase:
        return jsonify({"success": False, "message": "Database disconnected"}), 500
        
    data = request.json
    seat_id = data.get('id')

    if not seat_id:
        return jsonify({"success": False, "message": "Missing seat ID"}), 400

    try:
        seat_res = supabase.table('seats').select('*').eq('id', int(seat_id)).execute()
        if not seat_res.data:
            return jsonify({"success": False, "message": "Seat not found"}), 404
            
        seat = seat_res.data[0]
        if seat['status'] == "Available":
            return jsonify({"success": False, "message": "Seat is already available"}), 400
            
        supabase.table('seats').update({
            'status': 'Available',
            'name': '',
            'gender': ''
        }).eq('id', int(seat_id)).execute()
        
        return jsonify({"success": True, "message": f"Seat {seat_id} cancelled successfully!"})
    except Exception as e:
        return jsonify({"success": False, "message": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5001)
